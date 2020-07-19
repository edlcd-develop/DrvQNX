//============================================================================
// Name        : drvIR.cc
// Author      : Gurin Fedor
// Version     :
// Copyright   :
// Description : Hello World in C++, QNX-style
//============================================================================

#include <cstdlib>
#include <iostream>


#include <stdlib.h>
#include <stdio.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <hw/inout.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "trrel48.h"


typedef union {
        struct _pulse pulse;
        char msg[255];
} my_message_t;
#define MAX_TRREL48 8


struct trrel48DrvInst {
	uint8_t ready[MAX_TRREL48];
    uint16_t   baseAddr[MAX_TRREL48];
    uint8_t numBaseAddr;

    int currentState[MAX_TRREL48 * REL48_REGS];
}*pInst;
int server_coid;
/*
* Overrides what happens when resource manager is read from
*/
int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb)
{
        uint64_t nb = 4;

    if(pInst->numBaseAddr == 0)
    {
        //errnoSet(EINVAL);
        return 0;
    }

    if (msg->i.nbytes < sizeof(int) * MAX_TRREL48 * pInst->numBaseAddr)
    {
        //errnoSet(EINVAL);
        return 0;
    }
    SETIOV(ctp->iov, (const void *) pInst->currentState, sizeof(int) * REL48_REGS * pInst->numBaseAddr);
    return sizeof(int) * REL48_REGS * pInst->numBaseAddr;

        // Was message already sent
        //if (ocb->offset == nb) return 0;

        // We will return which ever is smaller the size of our data or the size of the buffer
        //nb = min(nb, msg->i.nbytes);

        // Set the number of bytes we will return
        _IO_SET_READ_NBYTES(ctp, nb);

        //iofunc_read_verify (ctp, msg, ocb, NULL);
        //uint32_t *ptr = (devUpvKl.mapAddr) + ocb->offset;
        // Copy data into reply buffer.
        //SETIOV(ctp->iov, (devUpvKl.mapAddr) + ocb->offset, nb);

        // Update offset into our data used to determine start position for next read.
        ocb->offset += nb;

        // If we are going to send any bytes update the access time for this resource.
        if (nb > 0) ocb->attr->flags |= IOFUNC_ATTR_ATIME;

        return(_RESMGR_NPARTS(1));
}
bool checkCard(uint16_t baseAddr,uint8_t offset, uint16_t mask,uint16_t code)
{
    uint16_t curCode=0x0;
    curCode = in16(baseAddr + offset);
    usleep(10);
    if((curCode&mask) == code)
        return true;

    return false;
}
/*
* Overrides what happens when resource manager is written to
*/
int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb) {
       // int nb = 0;


        struct trrel48WriteCmd_ cmd;

       memset((void*)&cmd,0,sizeof(cmd));
        int maxCh=0,i=0,j=0,bit;
        int word;
        int bitsRead=0;
        maxCh = REL48_CHANNELS_PER_BOARD * pInst->numBaseAddr;

        if(pInst->numBaseAddr == 0)
        {
                //errnoSet(ENODEV);
                return EBADF;
        }
        if (msg->i.nbytes != sizeof(struct trrel48WriteCmd_)) {
        //errnoSet(EINVAL);
        return EBADF;
    }
    resmgr_msgread(ctp,(void*)&cmd,msg->i.nbytes,msg->i.combine_len);

    //cmd = (struct trrel48WriteCmd *) ocb->hdr.attr;
    if (cmd.startChannel >= maxCh) {
        //errnoSet(ENOSPC);
        return EBADF;
    }
    bitsRead = 0;
    for(i = 0;i < pInst->numBaseAddr;i++)
    {
    	if(pInst->ready[i] == 0)
    		continue;
        for(j = 0;j < 2 * REL48_REGS;j = j + 2)
        {
           bit = 0;
           word = 0;
           do{
                word |= cmd.values[bitsRead++]<<bit;
                bit++;
           }while(REL48_WORD != bit);
           out16((uintptr_t)(pInst->baseAddr[i] + j), word);
        }
    }


        _IO_SET_WRITE_NBYTES (ctp, msg->i.nbytes);


        return _RESMGR_NPARTS(1);
}

/*
* Overrides what happens when resource manager is opened
* - Creates and opens device
*/
int io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra) {
        if ((server_coid = name_open(TRREL48_DEVNAME, 0)) == -1) {
                perror("name_open failed.");
                return EXIT_FAILURE;
        }
        return (iofunc_open_default (ctp, msg, handle, extra));
}
int io_devctl(resmgr_context_t *ctp, io_devctl_t *msg, iofunc_ocb_t *ocb)
{
   // int i=0;
    if(msg->i.dcmd == REL48_IO_ADD_BASE_ADR)
    {
    	uint16_t baseAddr = *((uint16_t*)_DEVCTL_DATA (msg->i));
        for(int i = 0; i < pInst->numBaseAddr; i++)
        {
        	if(pInst->baseAddr[i] == baseAddr)
            return EOK;
        }
        pInst->baseAddr[pInst->numBaseAddr] = baseAddr;

    	int res = mmap_device_io(REL48_REG_WINDOW,pInst->baseAddr[pInst->numBaseAddr]);

    	if(res == MAP_DEVICE_FAILED)
    	{
    		printf("trrel48 - io_devctl : Can`t map io-port device \n");
    		return ENOTTY;
    	}
    	/*for (i = 0; i < REL48_REGS; i++)
        {
        	pInst->currentState[i] = in16((uintptr_t)(pInst->baseAddr[pInst->numBaseAddr] + 2 * i));
        }*/

    	bool ready = checkCard(pInst->baseAddr[pInst->numBaseAddr],REL48_OFFSET_CHECK,REL48_MASK_CHECK,REL48_CODE_CHECK);
    	pInst->baseAddr[pInst->numBaseAddr] =  ready;
    	if(ready == true)
    		std::cout<<"TTREL is ready"<<std::endl;
        else
    	    std::cout<<"TTREL is fail"<<std::endl;

        pInst->numBaseAddr++;
        return EOK;
    }
    //errnoSet(ENOTTY);
    return ENOTTY;

}
int io_lseek(resmgr_context_t *ctp, io_lseek_t *msg, iofunc_ocb_t *ocb)
{
    ocb->offset = msg->i.offset;
    return _RESMGR_STATUS(ctp,0);
}
int main(int argc, char *argv[])
{
    dispatch_t* dpp;
    resmgr_io_funcs_t io_funcs;
    resmgr_connect_funcs_t connect_funcs;
    iofunc_attr_t ioattr;
    dispatch_context_t   *ctp;
    int id = -1;

    if(ThreadCtl(_NTO_TCTL_IO,0) == -1)
	{
		perror("ThreadCtl");
		return (!EOK);
	}
    pInst = (struct trrel48DrvInst *) malloc(sizeof(struct trrel48DrvInst));
    if (pInst == NULL) {
          return EXIT_FAILURE;
       }
    memset( (void *)pInst, 0, sizeof(struct trrel48DrvInst));

    dpp = dispatch_create();
    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs, _RESMGR_IO_NFUNCS, &io_funcs);
    connect_funcs.open = io_open;
    io_funcs.read  = io_read;
    io_funcs.write = io_write;
    io_funcs.lseek = io_lseek;
    io_funcs.devctl= io_devctl;

    iofunc_attr_init(&ioattr, S_IFCHR | 0666, NULL, NULL);

    id = resmgr_attach(dpp, NULL, TRREL48_DEVPATH, _FTYPE_ANY, 0, &connect_funcs, &io_funcs, &ioattr);
    if(id == -1)
         	std::cout<<"Can`t attach to TRREL48 device"<<std::endl;
    ctp = dispatch_context_alloc(dpp);
    while(1) {
            ctp = dispatch_block(ctp);
            dispatch_handler(ctp);
    }
    return EXIT_SUCCESS;
}

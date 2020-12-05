//============================================================================
// Name        : itp.cc
// Author      : Gurin Fedor
// Version     : 0.1
// Copyright   : 
// Description : Driver for ISA adapter ITP 
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

#include "itp.h"

//! Структура с описанием устройств
struct itpDrvInst 
{
    //! список признаков готовности устройств
    uint8_t    ready[ITP_MAX_ADAPTERS];
    //! список базовых адресов
    uint16_t   baseAddr[ITP_MAX_ADAPTERS];
    //! кол-во базовых адресов в списке
    uint8_t    numBaseAddr;
}*pInst;
int server_coid;

/*!
 * Overrides what happens when resource manager is written to
*/
int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb)
{

    itp_write_cmd cmd;

    memset((void*)&cmd,0,sizeof(cmd));

    int maxCh = ITP_CHANNELS_PER_BOARD * pInst->numBaseAddr;

    if(pInst->numBaseAddr == 0)
    {
         //errnoSet(ENODEV);
         return EBADF;
    }
    if (msg->i.nbytes != sizeof(itp_write_cmd))
    {
        //errnoSet(EINVAL);
        return EBADF;
    }
    resmgr_msgread(ctp,(void*)&cmd,msg->i.nbytes,msg->i.combine_len);

    if (cmd.numCh >= maxCh)
    {
        //errnoSet(ENOSPC);
        return EBADF;
    }
    int offset = 0;

    uint8_t numA = cmd.numCh / ITP_CHANNELS_PER_BOARD;
    uint16_t numCh = cmd.numCh - numA * ITP_CHANNELS_PER_BOARD ;
    if((numCh%2) > 0)
    	offset = 2;
    if(pInst->ready[numA] == 1)
    	out16((uintptr_t)(pInst->baseAddr[numA] + offset), cmd.value);

    _IO_SET_WRITE_NBYTES (ctp, msg->i.nbytes);
    return _RESMGR_NPARTS(1);
}

/*!
* Overrides what happens when resource manager is opened
* - Creates and opens device
*/
int io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra) {
        if ((server_coid = name_open(ITP_DEVNAME, 0)) == -1) {
                perror("name_open failed.");
                return EXIT_FAILURE;
        }
        return (iofunc_open_default (ctp, msg, handle, extra));
}
#define FOLDER_FIRMWARE "/home/conf/drv/"
//! Загрузка прошивок
void loadCard(std::string name, uint32_t init, uint32_t load)
{
        int fd;
        int bytesRead = 0;
        int size = 0;
        char buffer[255];

        std::string nameFile = FOLDER_FIRMWARE + name;

        //! запись прошивок
        fd = open(nameFile.c_str(), O_RDONLY,0);
        if (fd < 0)
        {
            std::cout<<"ITP DRV: Can`t open file = "<<nameFile<<std::endl;
            return;
        }

        lseek(fd,0,SEEK_SET);
        //! запись 0 для прошивок
        out16((uintptr_t)init,0);
        do {
            lseek(fd,size,SEEK_SET);
            bytesRead = read(fd,(char*)buffer, sizeof(char));
            size +=bytesRead;

            for(int shift=7;shift>=0;shift--)
            	out16((uintptr_t)load,buffer[0]>>shift);
            if(bytesRead <0)
            {
                std::cout<<"ITP_DRV: Can`t read file"<<std::endl;
                close(fd);
            }
        }while (bytesRead!=0);
        close(fd);

}
//! Проверка адаптера
bool checkCard(uint16_t baseAddr,uint8_t offset, uint16_t mask,uint16_t code)
{
    uint16_t curCode=0x0;
    curCode = in16(baseAddr + offset);
    usleep(10);
    if((curCode&mask) == code)
        return true;

    return false;
}

//! Обработка запросов ввода/вывода
int io_devctl(resmgr_context_t *ctp, io_devctl_t *msg, iofunc_ocb_t *ocb)
{
    //int i=0;
    if(msg->i.dcmd == ITP_IO_ADD_BASE_ADR)
    {
    	uint16_t baseAddr = *((uint16_t*)_DEVCTL_DATA (msg->i));
    	    	for(int i = 0; i < pInst->numBaseAddr; i++)
    	    	{
    	    		if(pInst->baseAddr[i] == baseAddr)
    	    			return EOK;
    	    	}
    	    	pInst->baseAddr[pInst->numBaseAddr] = baseAddr;
        int res = mmap_device_io(ITP_REG_WINDOW,pInst->baseAddr[pInst->numBaseAddr]);

        if(res == MAP_DEVICE_FAILED)
        {
            printf("ITP - io_devctl : Can`t map io-port device \n");
            return ENOTTY;
        }

        bool  ready = checkCard(pInst->baseAddr[pInst->numBaseAddr],ITP_OFFSET_CHECK,ITP_MASK_CHECK,ITP_CODE_CHECK);

        pInst->ready[pInst->numBaseAddr] = ready;
        if(ready == true)
        {
        	std::cout<<"ITP is already"<<std::endl;
        	return EOK;
        }
        ready = checkCard(pInst->baseAddr[pInst->numBaseAddr],ITP_OFFSET_CHECK,ITP_MASK_CHECK,ITP_CODE_CHECK);
        pInst->ready[pInst->numBaseAddr] = ready;
        if(ready == true)
           std::cout<<"ITP is ready"<<std::endl;
        else
           std::cout<<"ITP is fail"<<std::endl;

        pInst->numBaseAddr++;
        return EOK;
    }
    //errnoSet(ENOTTY);
    return ENOTTY;

//! Смещение внути устройства
int io_lseek(resmgr_context_t *ctp, io_lseek_t *msg, iofunc_ocb_t *ocb)
{
    ocb->offset = msg->i.offset;
    return _RESMGR_STATUS(ctp,0);
}
//! Основная точка входа
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
    pInst = (struct itpDrvInst *) malloc(sizeof(struct itpDrvInst));
    if (pInst == NULL) {
          return EXIT_FAILURE;
       }
    memset( (void *)pInst, 0, sizeof(struct itpDrvInst));

    dpp = dispatch_create();
    iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs, _RESMGR_IO_NFUNCS, &io_funcs);
    connect_funcs.open = io_open;
    //io_funcs.read  = io_read;
    io_funcs.write = io_write;
    io_funcs.lseek = io_lseek;
    io_funcs.devctl= io_devctl;

    iofunc_attr_init(&ioattr, S_IFCHR | 0666, NULL, NULL);

    id = resmgr_attach(dpp, NULL, ITP_DEVPATH, _FTYPE_ANY, 0, &connect_funcs, &io_funcs, &ioattr);
    if(id == -1)
      	std::cout<<"Can`t attach to ITP device"<<std::endl;
    ctp = dispatch_context_alloc(dpp);
    while(1) {
            ctp = dispatch_block(ctp);
            dispatch_handler(ctp);
    }
    return EXIT_SUCCESS;
}

//============================================================================
// Name        : upv.cc
// Author      : Gurin Fedor
// Version     : 0.1
// Copyright   : 
// Description : Driver for PCI-e (1.0) adapter UPV KL 
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
#include <errno.h>
#include <hw/pci.h>
#include <sys/mman.h>
#include "upv.h"
#include "upv_ioctl.h"

typedef  struct TDevUPV_KL_{
	uint64_t  baseAddr[UPV_MAX_ADAPTERS];
	uint64_t  size[UPV_MAX_ADAPTERS];
	uint8_t   numAddr;//numbers word
	uintptr_t mapAddr[UPV_MAX_ADAPTERS];

}TDevUPV_KL;

TDevUPV_KL devUpvKl;

int server_coid;
int io_read(resmgr_context_t *ctp, io_read_t *msg, RESMGR_OCB_T *ocb)
{
	uint64_t nb = 4;

    // Was message already sent
    if (ocb->offset == nb) return 0;

    // We will return which ever is smaller the size of our data or the size of the buffer
    //nb = min(nb, msg->i.nbytes);

    // Set the number of bytes we will return
    _IO_SET_READ_NBYTES(ctp, nb);

        //iofunc_read_verify (ctp, msg, ocb, NULL);
        uint32_t *ptr = (uint32_t*)(((uint32_t)devUpvKl.mapAddr) + ocb->offset);
        // Copy data into reply buffer.
        SETIOV(ctp->iov, ptr, nb);

        // Update offset into our data used to determine start position for next read.
        ocb->offset += nb;

        // If we are going to send any bytes update the access time for this resource.
        if (nb > 0) ocb->attr->flags |= IOFUNC_ATTR_ATIME;

        return(_RESMGR_NPARTS(1));
}

int io_mmap (resmgr_context_t *ctp, io_mmap_t *msg, RESMGR_OCB_T *ocb)
{
	printf("mmap\n");
	printf("offser = %d\n", msg->i.offset);
	//mmap(devUpvKl.numAddr,sizeof(devUpvKl.numAddr),PROT_WRITE | PROT_READ,MAP_FIXED, msg->i., 0);

	return EOK;
	//msg->i.offset

}

/*
* Overrides what happens when resource manager is written to
*/
int io_write(resmgr_context_t *ctp, io_write_t *msg, RESMGR_OCB_T *ocb)
{
//{ // Was message already sent
//    if (ocb->offset == nb) return 0;
//
//    // We will return which ever is smaller the size of our data or the size of the buffer
//    nb = min(nb, msg->i.nbytes);
//
//    // Set the number of bytes we will return
//    _IO_SET_READ_NBYTES(ctp, nb);
//
//    //iofunc_read_verify (ctp, msg, ocb, NULL);
//    uint32_t *ptr = (devUpvKl.mapAddr) + ocb->offset;
//    // Copy data into reply buffer.
//    SETIOV(ctp->iov, (devUpvKl.mapAddr) + ocb->offset, nb);
//
//    // Update offset into our data used to determine start position for next read.
//    ocb->offset += nb;
//
//    // If we are going to send any bytes update the access time for this resource.
//    if (nb > 0) ocb->attr->flags |= IOFUNC_ATTR_ATIME;
//
//    return(_RESMGR_NPARTS(1));
}

/*
* Overrides what happens when resource manager is opened
* - Creates and opens device
*/
int io_open(resmgr_context_t *ctp, io_open_t *msg, RESMGR_HANDLE_T *handle, void *extra) {
        if ((server_coid = name_open(UPV_DEVNAME, 0)) == -1) {
                perror("name_open failed.");
                return EXIT_FAILURE;
        }
        return (iofunc_open_default (ctp, msg, handle, extra));
}
int count = 0;
int io_devctl(resmgr_context_t *ctp, io_devctl_t *msg, iofunc_ocb_t *ocb)
{
    if(msg->i.dcmd == UPV_READ_ADDR)
    {
    	upv_write_cmd cmd;
    	uint32_t *data = (uint32_t*)_DEVCTL_DATA (msg->i);
    	memcpy((void*)&cmd,data, sizeof(cmd));
    	//printf("adapter0 = %d \n",cmd.offsetAddr);
    	//printf("idA = %d \n",cmd.idA);


    	cmd.value = *((uint32_t*)(((uint32_t)devUpvKl.mapAddr[cmd.idA]) + cmd.offsetAddr));
    	count++;
    	if(count>1000)
    	{
    		uint32_t val1 = *((uint32_t*)(((uint32_t)devUpvKl.mapAddr[0]) + cmd.offsetAddr));
    		uint32_t val2 = *((uint32_t*)(((uint32_t)devUpvKl.mapAddr[1]) + cmd.offsetAddr));
    		//printf("value0 = %d\n",val1);
    		//printf("value1 = %d\n",val2);
    		count=0;
    	}

    	//SETIOV(ctp->iov, &cmd, sizeof(cmd));
    	/* set up the number of bytes (returned by client's read()) */
    	//_IO_SET_WRITE_NBYTES (ctp, sizeof(cmd));
    	//memcpy((void*)data,(void*)&cmd,sizeof(cmd));
    	//printf("msg.retval = %d \n",msg->o.ret_val);
    	//printf("nbytes = %d \n",msg->o.nbytes);
    	//printf("size = %d \n",ctp->size);


    	//resmgr_msgwrite(ctp, &cmd,sizeof(upv_write_cmd),0);
		//SETIOV(ctp->iov, &cmd, sizeof(upv_write_cmd));


        return EOK;
    }else if(msg->i.dcmd == UPV_WRITE_ADDR)
    {

    	upv_write_cmd cmd;
    	memcpy((void*)&cmd,((uint16_t*)_DEVCTL_DATA (msg->i)), sizeof(cmd));

    	uint32_t *ptr = (uint32_t*)(devUpvKl.mapAddr[cmd.idA]);
    	//printf("reg = %d \n",ptr[UPV_REG_STATE_M1_AR]);
    	ptr[cmd.offsetAddr] = cmd.value;

    	//((uintptr_t*)(devUpvKl.mapAddr[cmd.idA] + cmd.offsetAddr)) = cmd.value;
    	//printf("reg = %d \n",ptr[UPV_REG_MAIN_STATE]);
    	//printf("value = %d \n",cmd.value);


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
//extern "C" void shutdown_system(int type,int flags);
int main(int argc, char *argv[])
{


    dispatch_t* dpp;
      resmgr_io_funcs_t io_funcs;
      resmgr_connect_funcs_t connect_funcs;
      iofunc_attr_t ioattr;
      dispatch_context_t   *ctp;

      memset( (void *)&devUpvKl, 0, sizeof(devUpvKl));

      if(ThreadCtl(_NTO_TCTL_IO,0) == -1)
        {
            perror("ThreadCtl");
            return (!EOK);
        }
      dpp = dispatch_create();
      iofunc_func_init(_RESMGR_CONNECT_NFUNCS, &connect_funcs, _RESMGR_IO_NFUNCS, &io_funcs);
      connect_funcs.open = io_open;
      //io_funcs.read  = io_read;
      //io_funcs.write = io_write;
      io_funcs.mmap  = io_mmap;
      //io_funcs.lseek = io_lseek;
      io_funcs.devctl= io_devctl;

      iofunc_attr_init(&ioattr, S_IFCHR | 0666, NULL, NULL);

      int id = resmgr_attach(dpp, NULL, UPV_DEVPATH, _FTYPE_ANY, 0, &connect_funcs, &io_funcs, &ioattr);

      int handle = pci_attach(0);
      pci_rescan_bus();
      uint32_t flags = PCI_INIT_ALL;//PCI_PERSIST|PCI_SEARCH_VENDEV|PCI_INIT_BASE0;
      uint16_t idx = 0;
      struct pci_dev_info info;
      memset( &info, 0, sizeof( info ) );

      info.DeviceId = 0x0007;
      info.VendorId = 0x10ee;

      for(int idx = 0; idx < UPV_MAX_ADAPTERS; idx ++)
      {
    	  void* hdl = pci_attach_device(
    			  NULL,flags,idx,
				  &info );
      	  if( hdl == NULL ) {
      		  printf("Unable to locate adapter = %d\n",idx );
      		  continue;
      	  }
      	  printf("add\n");
      	  devUpvKl.baseAddr[devUpvKl.numAddr] = info.PciBaseAddress[0];
      	  devUpvKl.size[devUpvKl.numAddr]     = info.BaseAddressSize[0];
      	  /*void * mmap_device_memory( void * addr,
                                 size_t len,
                                 int prot,
                                 int flags,
                                uint64_t physical );*/

      	  void *ptr = mmap_device_memory( 0, devUpvKl.size[devUpvKl.numAddr], PROT_READ|PROT_WRITE|PROT_NOCACHE, 0 , devUpvKl.baseAddr[devUpvKl.numAddr] );

      	  uintptr_t *ptrInt = (uint32_t*)ptr;
      	  //printf("State1 = %d \n", ptrInt[24818]);
      	  //printf("State2 = %d \n", ptrInt[24822]);
      	  devUpvKl.mapAddr[devUpvKl.numAddr] = (uintptr_t)ptr;
      	  //printf("index = %d \n", devUpvKl.numAddr);
      	  //printf("ptrInt = %d \n", &ptrInt[24818]);
      	  //printf("ptrInt = %d \n", &ptrInt[24818]);
          //printf("mapAddr = %d \n", devUpvKl.mapAddr[devUpvKl.numAddr]);

      	  devUpvKl.numAddr ++;
      }
      if(devUpvKl.numAddr == 0)
    	  system("shutdown -S reboot");
      ctp = dispatch_context_alloc(dpp);
      while(1) {
              ctp = dispatch_block(ctp);
              dispatch_handler(ctp);
      }
      return EXIT_SUCCESS;
}

//============================================================================
// Name        : upv.cc
// Author      : Gurin Fedor
// Version     : 0.2
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
    //! массив базовых адресов PCI устройства
    uint64_t  baseAddr[UPV_MAX_ADAPTERS];
    //! размер адресного пространства
    uint64_t  size[UPV_MAX_ADAPTERS];
    //! кол-во адресных пространств
    uint8_t   numAddr;
    //! mapped memory
    uintptr_t mapAddr[UPV_MAX_ADAPTERS];
}TDevUPV_KL;

TDevUPV_KL devUpvKl;

int server_coid;

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
int io_devctl(resmgr_context_t *ctp, io_devctl_t *msg, iofunc_ocb_t *ocb)
{
    int nbytes, status = 0 ;
    upv_write_cmd cmd;
    if((status = iofunc_devctl_default(ctp,msg,ocb)) != _RESMGR_DEFAULT)
    {
        return(status);
    }
    status  = nbytes = 0;
    uint32_t *data = (uint32_t*)_DEVCTL_DATA (msg->i);
    // извлекаем команду
    memcpy((void*)&cmd,data, sizeof(cmd));
    // получаем начало участка памяти адаптера под номером cmd.idA
    uint32_t *ptr = (uint32_t*)(devUpvKl.mapAddr[cmd.idA]);
    if(msg->i.dcmd == UPV_READ_ADDR)
    {
        // извлекаем данные из памяти
        cmd.value = ptr[cmd.offsetAddr];
        // копируем данные обратно в  msg
        memcpy((void*)data,(void*)&cmd,sizeof(cmd));

    }else if(msg->i.dcmd == UPV_WRITE_ADDR)
    {
        ptr[cmd.offsetAddr] = cmd.value;
        nbytes = 0;
    }
    memset(&msg->o,0,sizeof(msg->o));
    msg->o.ret_val = status;
    msg->o.nbytes = nbytes;

    return (_RESMGR_PTR(ctp,&msg->o,sizeof(msg->o) + msg->o.nbytes));

}
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
    io_funcs.devctl= io_devctl;
    iofunc_attr_init(&ioattr, S_IFCHR | 0666, NULL, NULL);
    int id = resmgr_attach(dpp, NULL, UPV_DEVPATH, _FTYPE_ANY, 0, &connect_funcs, &io_funcs, &ioattr);
    int handle = pci_attach(0);
    pci_rescan_bus();
    uint32_t flags = PCI_INIT_ALL;//PCI_PERSIST|PCI_SEARCH_VENDEV|PCI_INIT_BASE0;
    uint16_t idx = 0;
    struct pci_dev_info info;
    memset( &info, 0, sizeof( info ) );
    // идентификатор pci устройства
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
        printf("Detected adapter\n");
        devUpvKl.baseAddr[devUpvKl.numAddr] = info.PciBaseAddress[0];
        devUpvKl.size[devUpvKl.numAddr]     = info.BaseAddressSize[0];
        // отображаем память
        void *ptr = mmap_device_memory( 0, devUpvKl.size[devUpvKl.numAddr], PROT_READ|PROT_WRITE|PROT_NOCACHE, 0 , devUpvKl.baseAddr[devUpvKl.numAddr] );
        uintptr_t *ptrInt = (uint32_t*)ptr;
        // сохраняем адреса начала mapped memory
        devUpvKl.mapAddr[devUpvKl.numAddr] = (uintptr_t)ptr;
        // увеличиваем счетчик кол-ва адптеров
        devUpvKl.numAddr ++;
    }
    // устройство не загрузилось, требуется выполнить перезагрузку
    if(devUpvKl.numAddr == 0)
        system("shutdown -S reboot");
    ctp = dispatch_context_alloc(dpp);
    while(1) {
        ctp = dispatch_block(ctp);
        dispatch_handler(ctp);
    }
    return EXIT_SUCCESS;
}

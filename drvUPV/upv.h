#ifndef _UPV_IOS_H
#define _UPV_IOS_H

#include "upv_defs.h"

//! Максимальное кол-во адресов Arinc429 УПВ КЛ
#define NUM_MAX_ADDR_UPV 255
typedef struct upv_write_cmd_ {
    //! номер адаптера
    uint8_t  idA;
    //! смещение
    uint64_t offsetAddr;
    //! значение
    uint32_t value;
}upv_write_cmd;
    
typedef struct upv_init_cmd_ {

    //! номер канала
    uint8_t numCh;
    uint8_t io;
    uint8_t lenAddr;
    //! список адресов
    uint8_t listAddr[NUM_MAX_ADDR_UPV];
    //! тип передачи
    uint8_t typeTrans;
    //! Cкорость передачи и пауза
    uint8_t freq;
}upv_init_cmd;

#endif /* _UPV_IOS_H */

#ifndef _IR_IOS_H
#define _IR_IOS_H


#include "ir_defs.h"
#include "ir_ioctl.h"


typedef struct ir_write_cmd_ {

    uint16_t numCh;   /* номер канала */
    int16_t value; /* код сопротивления */
}Tir_write_cmd;
    

#endif /* _IR_IOS_H */

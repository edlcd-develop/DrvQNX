#ifndef _IR_IOS_H
#define _IR_IOS_H

#include "ir_defs.h"
#include "ir_ioctl.h"

//! Структура данных для обмена с драйвером устройства IR
typedef struct ir_write_cmd_ {
    uint16_t numCh; /*!< Номер канала */
    int16_t value;  /*!< Код  */
}Tir_write_cmd;
    

#endif /* _IR_IOS_H */

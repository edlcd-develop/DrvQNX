#ifndef _GEN4S_IOS_H
#define _GEN4S_IOS_H

#include "gen4s_defs.h"
#include "gen4s_ioctl.h"

//! Структура данных для обмена с драйвером устройства GEN4S
typedef struct gen4s_write_cmd_ {
    uint8_t mode;   /*!< Режим работы(0 - генертатор с регулируемой частотой и напряжением,1 - генератор с ругулируемой частотой) */
    uint8_t numCh;  /*!< Номер канала */
    uint16_t u1;    /*!< Код напряжения для фазы A  */
    uint16_t u2;    /*!< Код напряжения для фазы B  */
    uint16_t u3;    /*!< Код напряжения для фазы С  */
    uint8_t phase;  /*!< Разрешение фазы(A = 0x00, B = 0x1, C = 0x2, Резерв = 0x3) */
    float freq;     /*!< Частота напряжения */
}gen4s_write_cmd;
    

#endif /* _IP_IOS_H */

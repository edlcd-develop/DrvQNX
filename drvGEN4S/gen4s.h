#ifndef _GEN4S_IOS_H
#define _GEN4S_IOS_H


#include "gen4s_defs.h"
#include "gen4s_ioctl.h"

typedef struct gen4s_write_cmd_ {
    // 0 - генертатор с регулируемой частотой и напряжением
    // 1 - генератор с ругулируемой частотой
    uint8_t mode;   //режим работы
    uint8_t numCh;  //номер канала
    uint16_t u1;    //код напряжения для фазы A
    uint16_t u2;    //код напряжения для фазы B
    uint16_t u3;    //код напряжения для фазы С
    uint8_t phase;  //разрешение фазы(A = 0x00, B = 0x1, C = 0x2, Резерв = 0x3
    float freq;     //частота напряжения
}gen4s_write_cmd;
    

#endif /* _IP_IOS_H */

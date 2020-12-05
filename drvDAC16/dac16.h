#ifndef _DAC16_IOS_H
#define _DAC16_IOS_H

#include "dac16_defs.h"
#include "dac16_ioctl.h"

//! Структура данных для обмена с драйвером устройства DAC16
typedef struct dac16_write_cmd_ {
	/*!< Номер канала */
    uint16_t numCh;
	/*!< Код  */
    int16_t value;
}dac16_write_cmd;

#endif /* _DACWAV_IOS_H */

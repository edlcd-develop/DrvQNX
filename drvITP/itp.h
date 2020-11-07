#ifndef _ITP_IOS_H
#define _ITP_IOS_H

#include "itp_defs.h"
#include "itp_ioctl.h"

//! Структура данных для обмена с драйвером устройства ITP
typedef struct itp_write_cmd_ {
    uint16_t numCh; /*!< Номер канала */
    int16_t  value; /*!< Код  */
}itp_write_cmd;

#endif /* _ITP_IOS_H */

#ifndef _IP_IOS_H
#define _IP_IOS_H

#include "ip_defs.h"
#include "ip_ioctl.h"

//! Структура данных для обмена с драйвером устройства IP
typedef struct ip_write_cmd_ {

    uint16_t numCh; /*!< Номер канала */
    int16_t value;  /*!< Код  */
}ip_write_cmd;
    

#endif /* _IP_IOS_H */

#ifndef _TRREL48_IOS_H
#define _TRREL48_IOS_H

#include "trrel48_defs.h"

//! Структура данных для обмена с драйвером устройства REL48
struct trrel48WriteCmd_ {
    unsigned startChannel; /*!< Номер канала с которого буде осуществлена запись/чтение */
    unsigned channelCount; /*!< Кол-ко каналов */
    uint8_t values[REL48_CHANNELS_PER_BOARD * REL48_MAX_ADAPTER]; /*!<  Массив значений по указаным каналам */
}trrel48WriteCmd;

#endif /* _TRREL48_IOS_H */

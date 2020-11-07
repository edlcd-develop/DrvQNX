#ifndef _IP_DEFS_H
#define _IP_DEFS_H

//! Кол-во каналов на каждой плате IP  
#define IP_CHANNELS_PER_BOARD 16
//! Максимальное кол-во адаптеров IP
#define IP_MAX_ADAPTERS 8
#define IP_MAX_SELECTIONS 0x4000
//! Путь к устройству IP
#define IP_DEVPATH "/dev/local/ip"
//! Имя устройства IP
#define IP_DEVNAME "ip"
//! Смещение в адресном пространстве I/O для записи канала
#define IP_OFFSET_CH 4
//! Смещение в адресном пространстве I/O для записи значения
#define IP_OFFSET_VAL 6
//! Смещение в адресном пространстве I/O для проверки готовности устройства IP
#define IP_OFFSET_CHECK 4
//! Маска для выделения кода готовности адаптера IP
#define IP_MASK_CHECK 0xFFF0
//! Код готовности адаптера IP
#define IP_CODE_CHECK 0xF000
//! Размер адресного I/O пространства адаптера IP, байт
#define IP_REG_WINDOW 8

#endif /* _IP_DEFS_H */

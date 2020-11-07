#ifndef _ITP_DEFS_H
#define _ITP_DEFS_H

//! Кол-во каналов на каждой плате ITP   
#define ITP_CHANNELS_PER_BOARD 2
//! Максимальное кол-во адаптеров ITP
#define ITP_MAX_ADAPTERS 8

#define ITP_MAX_SELECTIONS 0x4000
//! Путь к устройству ITP
#define ITP_DEVPATH "/dev/local/itp"
//! Имя устройства ITP
#define ITP_DEVNAME "itp"
//! Смещение в адресном пространстве I/O для записи канала
#define ITP_OFFSET_CHECK 0
//! Маска для выделения кода готовности адаптера ITP
#define ITP_MASK_CHECK 0xFFFF
//! Код готовности адаптера ITP
#define ITP_CODE_CHECK 0x114
//! Размер адресного I/O пространства адаптера ITP, байт
#define ITP_REG_WINDOW 8   

#endif /* _ITP_DEFS_H */

#ifndef _IR_DEFS_H
#define _IR_DEFS_H

//! Кол-во каналов на каждой плате IR    
#define IR_CHANNELS_PER_BOARD 12
//! Максимальное кол-во адаптеров IR
#define IR_MAX_ADAPTERS 8

#define IR_MAX_SELECTIONS 0x4000
//! Путь к устройству IR
#define IR_DEVPATH "/dev/local/ir"
//! Имя устройства IR
#define IR_DEVNAME "ir"
//! Смещение в адресном пространстве I/O для записи канала
#define IR_OFFSET_CH 4
//! Смещение в адресном пространстве I/O для записи значения
#define IR_OFFSET_VAL 6
//! Смещение в адресном пространстве I/O для проверки готовности устройства IR
#define IR_OFFSET_CHECK 4
//! Маска для выделения кода готовности адаптера IR
#define IR_MASK_CHECK 0xFFF0
//! Код готовности адаптера IR
#define IR_CODE_CHECK 0xF000
//! Размер адресного I/O пространства адаптера IR, байт
#define IR_REG_WINDOW 8
  

#endif /* _IR_DEFS_H */

#ifndef _DAC16_DEFS_H
#define _DAC16_DEFS_H

//! Кол-во каналов на каждой плате DAC16
#define DAC16_CHANNELS_PER_BOARD 16
//! Максимальное кол-во адаптеров DAC16
#define DAC16_MAX_ADAPTERS 8
//! 
#define DAC16_MAX_SELECTIONS 0x4000
//! Путь к устройству DAC16
#define DAC16_DEVPATH "/dev/local/dac16"
//! Имя устройства DAC16
#define DAC16_DEVNAME "dac16"
//! Смещение в адресном пространстве I/O для записи канала
#define DAC16_OFFSET_CH 2
//! Смещение в адресном пространстве I/O для записи значения
#define DAC16_OFFSET_VAL 0
//! Смещение в адресном пространстве I/O для проверки готовности устройства 
#define DAC16_OFFSET_CHECK 0
//! Маска для выделения кода готовности адаптера DAC16
#define DAC16_MASK_CHECK 0x7000
//! Код готовности адаптера DAC16
#define DAC16_CODE_CHECK 0x5000
//! Размер адресного I/O пространства адаптера DAC16, байт
#define DAC16_REG_WINDOW 4

#endif /* _DAC16_DEFS_H */

#ifndef _GEN4S_DEFS_H
#define _GEN4S_DEFS_H

//! Кол-во каналов на каждой плате Gen4S
#define GEN4S_CHANNELS_PER_BOARD    8
//! Кол-во каналов с нерегулируемой частотой на каждой плате Gen4S
#define GEN4S_CHANNELS_PER_BOARD_NU 4
//! Кол-во каналов с регулируемой частотой на каждой плате Gen4S
#define GEN4S_CHANNELS_PER_BOARD_U  4
//! Максимальное кол-во адаптеров Gen4S
#define GEN4S_MAX_ADAPTERS 8

#define GEN4S_MAX_SELECTIONS 0x4000
//! Путь к устройству Gen4S
#define GEN4S_DEVPATH "/dev/local/gen4s"
//! Имя устройства Gen4S
#define GEN4S_DEVNAME "gen4s"
//! Смещение в адресном пространстве I/O для прошивки
#define GEN4S_BURN                   2
//! Смещение в адресном пространстве I/O для задания напряжения
#define GEN4S_OFFSET_U               4
//! Смещение в адресном пространстве I/O для делителя частоты
#define GEN4S_OFFSET_DIV_MAJOR       6
//! Смещение в адресном пространстве I/O для делителя частоты
#define GEN4S_OFFSET_DIV_MINOR  	 8
//! Смещение в адресном пространстве I/O для частоты (старшая часть)
#define GEN4S_OFFSET_FREQ_DIV_MAJOR  10
//! Смещение в адресном пространстве I/O для прошивки (младшая часть)
#define GEN4S_OFFSET_FREQ_DIV_MINOR  12

//! Смещение в адресном пространстве I/O для проверки готовности устройства 
#define GEN4S_OFFSET_CHECK 	0x4
//! Маска для выделения кода готовности адаптера Gen4S
#define GEN4S_MASK_CHECK 	0xFFFF
//! Код готовности адаптера DAC16
#define GEN4S_CODE_CHECK 	0x1104
//! Размер адресного I/O пространства адаптера Gen4S, байт
#define GEN4S_REG_WINDOW 	16

#endif /* _GEN4S_DEFS_H */

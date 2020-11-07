#ifndef __REL48_DEFS_H
#define __REL48_DEFS_H

#include "rel48_errno.h"

#include <devctl.h>

#define REL48_BADDR_SEP ","
//! Кол-во каналов на каждой плате REL48 
#define REL48_CHANNELS_PER_BOARD 48
//! Максимальное кол-во адаптеров REL48
#define REL48_MAX_ADAPTER 8
//! Кол-во слов адаптера REL48
#define REL48_WORD 16
//! Кол-во регстров для адаптера REL48
#define REL48_REGS 3
//! IOCTL команда для добавления базового адреса нового устройства REL48 
#define REL48_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  2, uint16_t)
//! Смещение в адресном пространстве I/O для проверки готовности устройства REL48
#define REL48_OFFSET_CHECK 6
//! Маска для выделения кода готовности адаптера REL48
#define REL48_MASK_CHECK 0xFFFF
//! Код готовности адаптера REL48
#define REL48_CODE_CHECK 0x7070
//! Размер адресного I/O пространства адаптера REL48, байт
#define REL48_REG_WINDOW 8


#endif /* __REL48_DEFS_H */ 

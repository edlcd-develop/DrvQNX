#ifndef __REL48_DEFS_H
#define __REL48_DEFS_H


#include "rel48_errno.h"

#include <devctl.h>

#define REL48_BADDR_SEP ","
#define REL48_CHANNELS_PER_BOARD 48
#define REL48_MAX_ADAPTER 8
#define REL48_WORD 16
#define REL48_REGS 3
#define REL48_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  2, uint16_t)

#define REL48_OFFSET_CHECK 6
#define REL48_MASK_CHECK 0xFFFF
#define REL48_CODE_CHECK 0x7070
#define REL48_REG_WINDOW 8


#endif /* __REL48_DEFS_H */ 

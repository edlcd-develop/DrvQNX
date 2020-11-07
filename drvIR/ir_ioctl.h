#ifndef _IR_IOCTL_H
#define _IR_IOCTL_H

#include <devctl.h>

//! IOCTL команда для добавления базового адреса нового устройства IR  
#define IR_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  5, uint16_t)
//! IOCTL команда для запуска прошивики ПЛИС адаптера IR
#define IR_IO_BURN_FLASH __DION(_DCMD_CHR, 55)


#endif /* _IR_IOCTL_H */

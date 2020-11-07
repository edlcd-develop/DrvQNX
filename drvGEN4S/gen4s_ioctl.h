#ifndef _GEN4S_IOCTL_H
#define _GEN4S_IOCTL_H

#include <devctl.h>
//! IOCTL команда для добавления базового адреса нового устройства GEN4S
#define GEN4S_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  7, uint16_t)
//! IOCTL команда для запуска прошивики ПЛИС адаптера GEN4S
#define GEN4S_IO_BURN_FLASH __DION(_DCMD_CHR, 77)

#endif /* _GEN4S_IOCTL_H */

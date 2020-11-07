#ifndef _IP_IOCTL_H
#define _IP_IOCTL_H

#include <devctl.h>
//! IOCTL команда для добавления базового адреса нового устройства IP    
#define IP_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  6, uint16_t)
//! IOCTL команда для запуска прошивики ПЛИС адаптера IP
#define IP_IO_BURN_FLASH __DION(_DCMD_CHR, 66)


#endif /* _IP_IOCTL_H */

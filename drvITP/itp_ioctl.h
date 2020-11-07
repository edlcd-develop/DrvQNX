#ifndef _ITP_IOCTL_H
#define _ITP_IOCTL_H

#include <devctl.h>

//! IOCTL команда для добавления базового адреса нового устройства ITP  
#define ITP_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  4, uint16_t)

#endif /* _ITP_IOCTL_H */

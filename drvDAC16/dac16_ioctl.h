#ifndef _DAC16_IOCTL_H
#define _DAC16_IOCTL_H

#include <devctl.h>
//! IOCTL команда для добавления базового адреса нового устройства DAC16
#define DAC16_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  3, uint16_t)

#endif /* _DAC16_IOCTL_H */

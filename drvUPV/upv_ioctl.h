#ifndef _UPV_IOCTL_H
#define _UPV_IOCTL_H

#include <devctl.h>
#include "upv.h"

//! IOCTL команда на чтение значения из адреса
#define UPV_READ_ADDR  __DIOTF(_DCMD_CHR,  200, upv_write_cmd)
//! IOCTL команда на запись значения по адресу
#define UPV_WRITE_ADDR __DIOT(_DCMD_CHR,  201, upv_write_cmd)
//! IOCTL команда инициализации устройства
#define UPV_INIT __DIOT(_DCMD_CHR,  202, upv_init_cmd)

#endif /* _GEN4S_IOCTL_H */

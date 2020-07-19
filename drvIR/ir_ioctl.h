#ifndef _IR_IOCTL_H
#define _IR_IOCTL_H

#include <devctl.h>



    
#define IR_IO_ADD_BASE_ADR __DIOT(_DCMD_CHR,  5, uint16_t)
#define IR_IO_BURN_FLASH __DION(_DCMD_CHR, 55)


#endif /* _IR_IOCTL_H */

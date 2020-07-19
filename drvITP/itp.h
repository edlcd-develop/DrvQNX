#ifndef _ITP_IOS_H
#define _ITP_IOS_H


#include "itp_defs.h"
#include "itp_ioctl.h"

typedef struct itp_write_cmd_ {
    uint16_t numCh;   /* номер канала */
    int16_t  value; /* код напряжения */
}itp_write_cmd;
    

#endif /* _DACWAV_IOS_H */

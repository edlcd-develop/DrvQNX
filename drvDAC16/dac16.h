#ifndef _DAC16_IOS_H
#define _DAC16_IOS_H

#include "dac16_defs.h"
#include "dac16_ioctl.h"

typedef struct dac16_write_cmd_ {
    uint16_t numCh;   /* номер канала */
    int16_t value; /* код  */
}dac16_write_cmd;

#endif /* _DACWAV_IOS_H */

#ifndef _IP_IOS_H
#define _IP_IOS_H


#include "ip_defs.h"
#include "ip_ioctl.h"


typedef struct ip_write_cmd_ {

    uint16_t numCh;   /* номер канала */
    int16_t value; /* код сопротивления */
}ip_write_cmd;
    

#endif /* _IP_IOS_H */

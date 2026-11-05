#include "area168_13.h"

MATCH void Fish_LocationMessage(void) {
    SYS_DISPATCH_BYTE(D_801F4B2C + 0xC, TASK_BYTES[0x1]);
}

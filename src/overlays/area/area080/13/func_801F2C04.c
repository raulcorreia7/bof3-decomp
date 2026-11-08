#include "area080_13.h"
#include "area/spad.h"

MATCH s32 func_801F2C04(void) {
    SYS_DISPATCH_BYTE(D_801F3DAC, g_Task->header.mode);
}

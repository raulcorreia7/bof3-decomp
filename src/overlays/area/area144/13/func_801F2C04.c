#include "area144_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH s32 func_801F2C04(void) {
    SYS_DISPATCH_BYTE(D_801F3E68, g_Task->header.mode);
}

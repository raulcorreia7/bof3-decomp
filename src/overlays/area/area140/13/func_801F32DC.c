#include "area140_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F32DC(void) {
    SYS_DISPATCH_BYTE(D_801F47DC, g_Task->header.step);
}

#include "area140_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F46A0(void) {
    SYS_DISPATCH_BYTE(D_801F4AC4, g_Task->header.mode);
}

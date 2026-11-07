#include "area145_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2C90(void) {
    SYS_DISPATCH_BYTE(D_801F5434, g_Task->header.mode);
}

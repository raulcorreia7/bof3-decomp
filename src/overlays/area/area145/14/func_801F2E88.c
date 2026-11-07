#include "area145_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2E88(void) {
    SYS_DISPATCH_BYTE(D_801F5454, g_Task->header.mode);
}

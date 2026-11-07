#include "area145_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F389C(void) {
    SYS_DISPATCH_BYTE(D_801F545C, g_Task->header.mode);
}

#include "area098_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F37D0(void) {
    SYS_DISPATCH_BYTE(D_801F5F88, g_Task->header.mode);
}

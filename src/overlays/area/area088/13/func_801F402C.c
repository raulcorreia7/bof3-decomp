#include "area088_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F402C(void) {
    SYS_DISPATCH_BYTE(D_801F61BC, g_Task->header.step);
}

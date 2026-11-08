#include "area148_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F35D8(void) {
    SYS_DISPATCH_BYTE(D_801F5024, g_Task->header.step);
}

#include "area135_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2C8C(void) {
    SYS_DISPATCH_BYTE(D_801F61F8, g_Task->header.mode);
}

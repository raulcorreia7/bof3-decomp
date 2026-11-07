#include "area143_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3F04(void) {
    SYS_DISPATCH_BYTE(D_801F5308, g_Task->header.mode);
}

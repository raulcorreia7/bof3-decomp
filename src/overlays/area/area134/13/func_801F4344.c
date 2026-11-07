#include "area134_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F4344(void) {
    SYS_DISPATCH_BYTE(D_801F5828, g_Task->header.mode);
}

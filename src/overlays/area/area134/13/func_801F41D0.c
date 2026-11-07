#include "area134_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F41D0(void) {
    SYS_DISPATCH_BYTE(D_801F581C, g_Task->header.mode);
}

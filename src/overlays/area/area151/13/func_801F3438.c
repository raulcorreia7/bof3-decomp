#include "area151_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3438(void) {
    SYS_DISPATCH_BYTE(D_801F5448, g_Task->header.step);
}

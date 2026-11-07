#include "area139_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3A8C(void) {
    SYS_DISPATCH_BYTE(D_801F4448, g_Task->header.step);
}

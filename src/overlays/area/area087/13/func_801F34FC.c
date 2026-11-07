#include "area087_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F34FC(void) {
    SYS_DISPATCH_BYTE(D_801F5750, g_Task->header.step);
}

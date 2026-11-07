#include "area151_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F338C(void) {
    SYS_DISPATCH_BYTE(D_801F5440, g_Task->header.mode);
}

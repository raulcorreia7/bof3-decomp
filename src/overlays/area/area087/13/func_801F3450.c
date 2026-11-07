#include "area087_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3450(void) {
    SYS_DISPATCH_BYTE(D_801F5748, g_Task->header.mode);
}

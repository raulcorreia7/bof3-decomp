#include "area088_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F4CD8(void) {
    SYS_DISPATCH_BYTE(D_801F624C, g_Task->header.mode);
}

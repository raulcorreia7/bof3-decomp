#include "area148_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F427C(void) {
    SYS_DISPATCH_BYTE(D_801F6160, g_Task->header.mode);
}

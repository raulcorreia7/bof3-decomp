#include "area151_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F35FC(void) {
    SYS_DISPATCH_BYTE(D_801F5458, g_Task->unk_03);
}

#include "area135_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F4D88(void) {
    SYS_DISPATCH_BYTE(D_801F6B48, g_Task->unk_04);
}

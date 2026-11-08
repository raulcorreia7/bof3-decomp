#include "area135_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F4ED4(void) {
    SYS_DISPATCH_BYTE(D_801F6B6C, g_Task->unk_04);
}

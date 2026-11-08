#include "area149_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2EFC(void) {
    SYS_DISPATCH_BYTE(D_801F4580, g_Task->unk_04);
}

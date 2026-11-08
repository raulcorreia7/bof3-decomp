#include "area141_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3838(void) {
    SYS_DISPATCH_BYTE(D_801F4DCC, g_Task->unk_04);
}

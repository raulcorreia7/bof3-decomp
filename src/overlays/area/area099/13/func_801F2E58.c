#include "area099_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2E58(void) {
    SYS_DISPATCH_BYTE(D_801F49A0, g_Task->unk_04);
}

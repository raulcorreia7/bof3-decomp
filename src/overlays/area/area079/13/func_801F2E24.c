#include "area079_13.h"
#include "area/spad.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2E24(void) {
    SYS_DISPATCH_BYTE(D_801F4C7C, g_Task->unk_04);
}

#include "area141_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2CE8(void) {
    SYS_DISPATCH_BYTE(D_801F47E8, TASK_BYTES[0x2]);
}

#include "area145_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3DCC(void) {
    SYS_DISPATCH_BYTE(D_801F5C94, TASK_BYTES[0x4]);
}

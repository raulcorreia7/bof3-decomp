#include "area085_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F309C(void) {
    SYS_DISPATCH_BYTE(D_801F3D40, TASK_BYTES[0x1]);
}

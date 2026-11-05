#include "area147_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2C04(void) {
    SYS_DISPATCH_BYTE(D_801F358C, TASK_BYTES[0x2]);
}

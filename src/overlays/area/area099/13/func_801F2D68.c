#include "area099_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2D68(void) {
    SYS_DISPATCH_BYTE(D_801F4988, TASK_BYTES[0x4]);
}

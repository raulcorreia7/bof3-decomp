#include "area146_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2D90(void) {
    SYS_DISPATCH_BYTE(D_801F3B00, TASK_BYTES[0x1]);
}

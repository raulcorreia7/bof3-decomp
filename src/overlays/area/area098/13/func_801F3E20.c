#include "area098_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3E20(void) {
    SYS_DISPATCH_BYTE(D_801F5FAC, TASK_BYTES[0x1]);
}

#include "area088_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F512C(void) {
    SYS_DISPATCH_BYTE(D_801F6270, TASK_BYTES[0x1]);
}

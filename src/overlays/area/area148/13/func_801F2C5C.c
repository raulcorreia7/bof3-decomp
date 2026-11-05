#include "area148_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F2C5C(void) {
    SYS_DISPATCH_BYTE(D_801F4FC4, TASK_BYTES[0x2]);
}

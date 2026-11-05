#include "area135_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F344C(void) {
    SYS_DISPATCH_BYTE(D_801F6218, TASK_BYTES[0x1]);
}

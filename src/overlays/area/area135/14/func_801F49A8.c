#include "area135_14.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F49A8(void) {
    SYS_DISPATCH_BYTE(D_801F6B34, TASK_BYTES[0x4]);
}

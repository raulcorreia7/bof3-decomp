#include "area142_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3414(void) {
    SYS_DISPATCH_BYTE(D_801F3B7C, TASK_BYTES[0x4]);
}

#include "area151_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F35FC(void) {
    SYS_DISPATCH_BYTE(D_801F5458, TASK_BYTES[0x3]);
}

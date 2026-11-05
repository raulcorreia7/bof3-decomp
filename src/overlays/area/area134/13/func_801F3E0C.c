#include "area134_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3E0C(void) {
    SYS_DISPATCH_BYTE(D_801F5804, TASK_BYTES[0x1]);
}

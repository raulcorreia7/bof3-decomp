#include "area088_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3F80(void) {
    SYS_DISPATCH_BYTE(D_801F61B4, TASK_BYTES[0x1]);
}

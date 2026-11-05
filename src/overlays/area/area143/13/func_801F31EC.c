#include "area143_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F31EC(void) {
    SYS_DISPATCH_BYTE(D_801F4314, TASK_BYTES[0x2]);
}

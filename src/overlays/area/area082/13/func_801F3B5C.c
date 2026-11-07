#include "area082_13.h"

/* Dispatch the scratchpad state byte through the overlay's handler table. */
MATCH void func_801F3B5C(void) {
    SYS_DISPATCH_BYTE(D_801F576C, g_Task->header.step);
}

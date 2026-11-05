#include "area030_04.h"

/* Reads byte 0x01 of the scratchpad work object pointed at by the
 * non-volatile pointer cell at 0x1F800044, then calls the handler stored at
 * that index in the D_801E1D80 dispatch table. */
MATCH void func_801D2BF0(void) {
    u8*      work;
    Callback handler;

    work    = TASK_BYTES;
    handler = D_801E1D80[work[1]];
    handler();
}

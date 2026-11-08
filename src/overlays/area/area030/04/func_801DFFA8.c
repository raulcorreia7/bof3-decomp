#include "area030_04.h"

/* Reads the byte at offset 0x02 of the scratchpad work object
 * pointed at by the non-volatile pointer cell at 0x1F800044, then calls the
 * handler stored at that index in the D_801E2340 dispatch table. */
MATCH void func_801DFFA8(void) {
    Callback handler;

    handler = D_801E2340[g_Task->header.step];
    handler();
}

#include "area030_04.h"

/* Reads the byte at offset 0x02 of the scratchpad work object pointed at by the non-volatile pointer cell at 0x1F800044. */
MATCH void func_801E00E0(void) {
    Callback handler;

    handler = D_801E2348[g_Task->header.step];
    handler();
}

#include "area030_04.h"

/* Reads the byte at offset 0x03 of the scratchpad work object pointed at by the non-volatile pointer cell at 0x1F800044. */
MATCH void func_801DDBC8(void) {
    Callback handler;

    handler = D_801E2304[g_Task->unk_03];
    handler();
}

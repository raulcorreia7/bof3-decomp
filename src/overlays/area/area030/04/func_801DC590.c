/* Reads the byte at offset 0x03 of the scratchpad work object pointed at by the non-volatile pointer cell at 0x1F800044. */

#include "area030_04.h"

MATCH void func_801DC590(void) {
    Callback handler = D_801E22B0[g_Task->unk_03];
    handler();
}

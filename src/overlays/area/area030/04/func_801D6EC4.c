/* Reads the byte at offset 0x03 of the scratchpad work object pointed at by the non-volatile pointer cell at 0x1F800044. */

#include "area030_04.h"

MATCH void func_801D6EC4(void) {
    Callback handler = D_801E20C4[g_Task->unk_03];
    handler();
}

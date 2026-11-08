/* Reads the byte at offset 0x03 of the scratchpad work object
 * pointed at by the non-volatile pointer cell at 0x1F800044, then calls the
 * handler stored at that index in the D_801E2048 dispatch table. */

#include "area030_04.h"

MATCH void func_801D6554(void) {
    u8*      work    = (u8*)g_Task;
    Callback handler = D_801E2048[work[3]];
    handler();
}

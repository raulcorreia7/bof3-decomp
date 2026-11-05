/* Reads the byte at offset 0x03 of the scratchpad work object
 * pointed at by the non-volatile pointer cell at 0x1F800044, then calls the
 * handler stored at that index in the D_801E221C dispatch table. */

#include "area030_04.h"

MATCH void func_801D9CF4(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = D_801E221C[work[3]];
    handler();
}

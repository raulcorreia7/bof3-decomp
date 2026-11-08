#include "area030_04.h"

/* Reads the byte at offset 0x03 of the scratchpad work object
 * pointed at by the non-volatile pointer cell at 0x1F800044, then calls the
 * handler stored at that index in the D_801E22FC dispatch table. */
MATCH void func_801DD95C(void) {
    u8*      work;
    Callback handler;

    work    = (u8*)g_Task;
    handler = D_801E22FC[work[3]];
    handler();
}

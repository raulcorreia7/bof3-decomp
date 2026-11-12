#include "area030_04.h"

/* Calls `Fishing_DrawDimScreen`, then calls the handler stored at index
 * byte 0x03 of the scratchpad work object in the D_801E22D0 dispatch table. */
MATCH void func_801DC838(void) {
    Callback handler;

    Fishing_DrawDimScreen();
    handler = D_801E22D0[g_Task->unk_03];
    handler();
}

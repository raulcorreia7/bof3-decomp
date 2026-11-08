#include "area030_04.h"

/* Calls `func_801E16DC`, then calls the handler stored at index
 * byte 0x03 of the scratchpad work object in the D_801E22D0 dispatch table. */
MATCH void func_801DC838(void) {
    Callback handler;

    func_801E16DC();
    handler = D_801E22D0[g_Task->unk_03];
    handler();
}

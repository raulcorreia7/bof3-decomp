#include "engine/slus/slus.h"

/* dispatches the selected handler (slot byte g_MessageChoiceStep) of the two
 * table entries stored on the stack, then decrements the pending-halfword
 * counter g_MessageChoiceTimer when it is not 0xFFFF.
 */
/* FAKE: barrier holds the handler-pointer stores after the ra spill so the
 * prologue store stays in the second slot. */
MATCH void func_80151A98(void) {
    Table2 table = {{func_80151B08, func_80151B50}};

    table.handlers[g_MessageChoiceStep]();
    if (g_MessageChoiceTimer != 0xFFFFu) {
        g_MessageChoiceTimer -= 1;
    }
}

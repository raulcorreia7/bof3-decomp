#include "engine/slus/slus.h"

/* dispatches the handler the pending step byte g_MessageChoiceStep selects
 * through the two-entry table stored on the stack, then counts the pending
 * halfword g_MessageChoiceTimer down unless it is 0xFFFF, and clears g_MessageChoiceMode when the
 * count reaches zero.
 */
MATCH void UI_RunChoiceStep(void) {
    Table2 table = {{func_801519F8, func_80151A48}};

    table.handlers[g_MessageChoiceStep]();
    if (g_MessageChoiceTimer != 0xFFFFu) {
        g_MessageChoiceTimer -= 1;
    }
    if (g_MessageChoiceTimer == 0) {
        g_MessageChoiceMode = 0;
    }
}

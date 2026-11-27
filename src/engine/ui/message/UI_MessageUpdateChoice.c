#include "engine/slus/slus.h"

/* dispatches the handler the pending step byte g_UIMessageChoiceStep selects
 * through the two-entry table stored on the stack, then counts the pending
 * halfword g_UIMessageChoiceTimer down unless it is 0xFFFF, and clears g_UIMessageChoiceMode when the
 * count reaches zero.
 */
MATCH void UI_MessageUpdateChoice(void) {
    ChoiceSteps table = {{UI_MessageNextChoice, UI_MessagePrevChoice}};

    table.steps[g_UIMessageChoiceStep]();
    if (g_UIMessageChoiceTimer != 0xFFFFu) {
        g_UIMessageChoiceTimer -= 1;
    }
    if (g_UIMessageChoiceTimer == 0) {
        g_UIMessageChoiceMode = 0;
    }
}

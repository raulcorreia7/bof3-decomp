#include "engine/slus/slus.h"

/* dispatches the handler the pending step byte g_UiMessageChoiceStep selects
 * through the two-entry table stored on the stack, then counts the pending
 * halfword g_UiMessageChoiceTimer down unless it is 0xFFFF, and clears g_UiMessageChoiceMode when the
 * count reaches zero.
 */
MATCH void UI_MessageUpdateChoice(void) {
    ChoiceSteps table = {{UI_MessageNextChoice, UI_MessagePrevChoice}};

    table.steps[g_UiMessageChoiceStep]();
    if (g_UiMessageChoiceTimer != 0xFFFFu) {
        g_UiMessageChoiceTimer -= 1;
    }
    if (g_UiMessageChoiceTimer == 0) {
        g_UiMessageChoiceMode = 0;
    }
}

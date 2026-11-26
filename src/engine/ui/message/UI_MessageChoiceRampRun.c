#include "engine/slus/slus.h"

/* FAKE: barrier holds the handler-pointer stores after the ra spill so the
 * prologue store stays in the second slot. */
/* func_80151A98 */
/* Runs the ramp handler that the choice step selects, then counts the choice timer down unless it is 0xFFFF. */
MATCH void UI_MessageChoiceRampRun(void) {
    ChoiceSteps table = {{UI_MessageChoiceRampBegin, UI_MessageChoiceRampStep}};

    table.steps[g_UiMessageChoiceStep]();
    if (g_UiMessageChoiceTimer != 0xFFFFu) {
        g_UiMessageChoiceTimer -= 1;
    }
}

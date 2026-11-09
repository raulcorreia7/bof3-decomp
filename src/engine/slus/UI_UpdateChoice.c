#include "engine/slus/slus.h"

/* dispatches the handler the pending step byte g_MessageChoiceStep selects through the two-entry table stored on the stack. */
MATCH void UI_UpdateChoice(void) {
    Table2 table = {{UI_NextChoice, UI_PrevChoice}};

    table.handlers[g_MessageChoiceStep]();
    if (g_MessageChoiceTimer != 0xFFFFu) {
        g_MessageChoiceTimer -= 1;
    }
    if (g_MessageChoiceTimer == 0) {
        g_MessageChoiceMode = 0;
    }
}

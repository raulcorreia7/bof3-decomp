#include "engine/slus/slus.h"

/* Steps on once the choice panel is open and the message panel is closed. */
MATCH void UI_MessageWaitChoiceReady(void) {
    if ((g_UiPanelTasks[1].state == 2) && (g_UiPanelTasks[0].state == 4)) {
        /* FAKE: retail addresses g_UiMessageStep as an array element; the scalar spelling folds the address. */
        MEM(u8, (u32)&g_UiMessageStep) += 1;
    }
}

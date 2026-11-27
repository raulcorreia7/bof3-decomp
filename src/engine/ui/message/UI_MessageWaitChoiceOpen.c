#include "engine/slus/slus.h"

/* Steps on once the choice panel is open. */
MATCH void UI_MessageWaitChoiceOpen(void) {
    if (g_UIPanelTasks[1].state == 2) {
        /* FAKE: retail addresses g_UIMessageStep as an array element; the scalar spelling folds the address. */
        MEM(u8, (u32)&g_UIMessageStep) += 1;
    }
}

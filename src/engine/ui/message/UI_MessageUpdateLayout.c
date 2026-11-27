#include "engine/slus/slus.h"

/* rebuilds the two window cells from the packed halfwords
 * D_80148334/D_80148336, runs the layout and selection passes, and reports
 * whether the shared word's confirm bit is clear.
 */
MATCH s32 UI_MessageUpdateLayout(void) {
    u16 confirm;

    /* D_80148334/D_80148336 stay address symbols: a g_UIPanelTasks[0].pos view changes the code. */
    g_UIMessageWindow.origin.x = (D_80148334 >> 4) + 10;
    g_UIMessageWindow.origin.y = (g_UIPanelTasks[0].pos.vy >> 4) + 6;
    UI_MessageDispatchState();
    UI_MessageDispatchChoiceMode();
    if ((g_UIWindowChannel & FRONTEND_FLAG_SELECTION) == 0) {
        UI_MessageDrawScript();
    }
    confirm = g_UIWindowChannel & FRONTEND_FLAG_CONFIRM;
    return confirm == 0;
}

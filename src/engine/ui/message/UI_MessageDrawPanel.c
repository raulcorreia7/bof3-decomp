#include "engine/slus/slus.h"

/* func_80159510 */
MATCH void UI_MessageDrawPanel(void) {
    MenuPanelTask* task;
    task = g_UiPanelCurrent;
    if (!(task->flags & 0x1)) {
        UI_WindowDrawPanelBox(task->pos.vx >> 4, task->pos.vy >> 4, (u8)(task->u.grow.w >> 4), (u8)(task->u.grow.h >> 4));
    }
    UI_MessageUpdateLayout();
}

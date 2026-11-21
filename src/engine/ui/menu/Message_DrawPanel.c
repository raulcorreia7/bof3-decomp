#include "engine/slus/slus.h"

/* func_80159510 */
MATCH void Message_DrawPanel(void) {
    MenuPanelTask* task;
    task = g_MenuCurrentPanel;
    if (!(task->flags & 0x1)) {
        UI_DrawPanelBox((s16)task->pos.x >> 4, (s16)task->pos.y >> 4, (u8)(task->u.grow.w >> 4), (u8)(task->u.grow.h >> 4));
    }
    Message_UpdateLayout();
}

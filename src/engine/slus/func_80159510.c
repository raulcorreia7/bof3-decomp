#include "engine/slus/slus.h"

MATCH void func_80159510(void) {
    MenuPanelTask* task;
    task = g_MenuCurrentPanel;
    if (!(task->flags & 0x1)) {
        UI_DrawPanelBox((s16)task->pos.x >> 4, (s16)task->pos.y >> 4, (u8)(task->u.grow.width >> 4), (u8)(task->u.grow.height >> 4));
    }
    UI_UpdateLayout();
}

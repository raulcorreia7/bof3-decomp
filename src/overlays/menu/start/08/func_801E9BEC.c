#include "start_08.h"

/* File-local declarations: the panel state handler table and the draw helpers
 * owned by this target or the executable. */

/* The shared MenuPanelTask view types the icon cursor at 0x10 as unk_10; the
 * accesses here are signed halfword loads. */
#define ICON_TASK   ((MenuPanelTask*)g_MenuCurrentPanel)
#define ICON_CURSOR (*(s16*)&ICON_TASK->unk_10)

MATCH void func_801E9BEC(void) {
    D_801ED420[ICON_TASK->state]();
    Menu_DrawHeaderBar(ICON_TASK->pos.x, ICON_TASK->pos.y, 0x118, 0x13, g_WindowStyle);
    if (ICON_CURSOR != 0) {
        WinDrawCueText((ICON_TASK->pos.x + 7), (ICON_TASK->pos.y + 3), (u16)ICON_CURSOR);
        if (ICON_CURSOR == 0x1A || ICON_CURSOR == 0x31) {
            WinDrawCueText((ICON_TASK->pos.x + 7), (ICON_TASK->pos.y + 3), 0xF);
        }
    }
}

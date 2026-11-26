#include "start_08.h"

/* File-local declarations: the panel state handler table and the draw helpers
 * owned by this target or the executable. */

/* The shared MenuPanelTask view types the icon cursor at 0x10 as unk_10; the
 * accesses here are signed halfword loads. */
#define ICON_TASK   ((MenuPanelTask*)g_UiPanelCurrent)
#define ICON_CURSOR (*(s16*)&ICON_TASK->u.message.id)

MATCH void Menu_MessagePanel(void) {
    g_MenuStartMessageSteps[ICON_TASK->state]();
    Menu_DrawHeaderBar((u16)ICON_TASK->pos.vx, (u16)ICON_TASK->pos.vy, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    if (ICON_CURSOR != 0) {
        WinDrawCueText((ICON_TASK->pos.vx + 7), (ICON_TASK->pos.vy + 3), (u16)ICON_CURSOR);
        if (ICON_CURSOR == 0x1A || ICON_CURSOR == 0x31) {
            WinDrawCueText((ICON_TASK->pos.vx + 7), (ICON_TASK->pos.vy + 3), 0xF);
        }
    }
}

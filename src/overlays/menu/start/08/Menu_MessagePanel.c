#include "start_08.h"

/* File-local declarations: the panel state handler table and the draw helpers owned by this target or the executable. */

/* The shared MenuPanelTask view types the icon cursor at 0x10 as unk_10. */
#define ICON_TASK   ((MenuPanelTask*)g_MenuCurrentPanel)
#define ICON_CURSOR (*(s16*)&ICON_TASK->u.message.id)

MATCH void Menu_MessagePanel(void) {
    g_MenuStartMessageStates[ICON_TASK->state]();
    Menu_DrawHeaderBar(ICON_TASK->pos.x, ICON_TASK->pos.y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    if (ICON_CURSOR != 0) {
        WinDrawCueText((ICON_TASK->pos.x + 7), (ICON_TASK->pos.y + 3), (u16)ICON_CURSOR);
        if (ICON_CURSOR == 0x1A || ICON_CURSOR == 0x31) {
            WinDrawCueText((ICON_TASK->pos.x + 7), (ICON_TASK->pos.y + 3), 0xF);
        }
    }
}

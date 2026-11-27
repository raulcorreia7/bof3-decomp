#include "shop_00.h"

/* File-local declarations: the shared fill-style byte, the panel state handler
 * table and the icon draw helpers owned by this target or the executable. */

#define ICON_CURSOR ((s16)g_UIPanelCurrent->u.message.id)

MATCH void Menu_MessagePanel(void) {
    g_ShopMessageSteps[g_UIPanelCurrent->state]();
    Menu_DrawHeaderBar((u16)g_UIPanelCurrent->pos.vx, (u16)g_UIPanelCurrent->pos.vy, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
    if (ICON_CURSOR != 0) {
        WinDrawCueText((g_UIPanelCurrent->pos.vx + 7), (g_UIPanelCurrent->pos.vy + 3), (u16)ICON_CURSOR);
        if (ICON_CURSOR == 0x36 || (u16)(ICON_CURSOR - 0x49) < 2 || ICON_CURSOR == 0x52) {
            WinDrawCueText((g_UIPanelCurrent->pos.vx + 7), (g_UIPanelCurrent->pos.vy + 3), 0xF);
        }
    }
}

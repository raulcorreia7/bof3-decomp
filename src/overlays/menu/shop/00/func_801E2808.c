#include "shop_00.h"

/* File-local declarations: the shared fill-style byte, the panel state handler
 * table and the icon draw helpers owned by this target or the executable. */

#define ICON_CURSOR ((s16)g_MenuCurrentPanel->unk_10)

MATCH void func_801E2808(void) {
    g_ShopPanel0StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawHeaderBar(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT,
                       g_WindowStyle);
    if (ICON_CURSOR != 0) {
        WinDrawCueText((g_MenuCurrentPanel->pos.x + 7), (g_MenuCurrentPanel->pos.y + 3), (u16)ICON_CURSOR);
        if (ICON_CURSOR == 0x36 || (u16)(ICON_CURSOR - 0x49) < 2 || ICON_CURSOR == 0x52) {
            WinDrawCueText((g_MenuCurrentPanel->pos.x + 7), (g_MenuCurrentPanel->pos.y + 3), 0xF);
        }
    }
}

#include "shop_00.h"

/* func_801E2AB0 */
MATCH void Menu_ZennyPanel(void) {
    g_ShopZennyStates[g_MenuCurrentPanel->state]();
    Menu_DrawZennyWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0, g_Zenny);
}

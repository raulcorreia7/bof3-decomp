#include "shop_00.h"

MATCH void func_801E2AB0(void) {
    g_ShopPanel1StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawZennyWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0, g_Zenny);
}

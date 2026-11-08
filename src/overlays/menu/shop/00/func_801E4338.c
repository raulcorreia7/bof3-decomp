#include "shop_00.h"

MATCH void func_801E4338(void) {
    g_ShopPanel16StateFuncs[g_MenuCurrentPanel->state]();
    Shop_DrawCuePanel(g_MenuCurrentPanel);
}

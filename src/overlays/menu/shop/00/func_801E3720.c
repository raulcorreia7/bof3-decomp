#include "shop_00.h"

MATCH void func_801E3720(void) {
    g_ShopPanel9StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawInventoryWindow(g_MenuCurrentPanel);
}

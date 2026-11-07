#include "shop_00.h"

MATCH void func_801E2EB0(void) {
    g_ShopPanel7StateFuncs[g_MenuCurrentPanel->state]();
    Shop_DrawItems((MenuListPanel*)g_MenuCurrentPanel);
}

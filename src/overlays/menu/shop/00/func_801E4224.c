#include "shop_00.h"

MATCH void func_801E4224(void) {
    g_ShopPanel15StateFuncs[g_MenuCurrentPanel->state]();
    func_801E45C0(g_MenuCurrentPanel);
}

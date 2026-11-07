#include "shop_00.h"

MATCH void func_801E3CF8(void) {
    g_ShopPanel12StateFuncs[g_MenuCurrentPanel->state]();
    func_801E1710(g_MenuCurrentPanel);
}

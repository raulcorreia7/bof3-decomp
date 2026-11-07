#include "shop_00.h"

MATCH void func_801E3BA4(void) {
    g_ShopPanel11StateFuncs[g_MenuCurrentPanel->state]();
    func_801E112C(g_MenuCurrentPanel);
}

#include "shop_00.h"

MATCH void func_801E440C(void) {
    g_ShopPanel17StateFuncs[g_MenuCurrentPanel->state]();
    func_801E4E9C(g_MenuCurrentPanel);
}

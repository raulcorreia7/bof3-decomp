#include "shop_00.h"

MATCH void func_801E44E0(void) {
    g_ShopPanel18StateFuncs[g_MenuCurrentPanel->state]();
    func_801E1E80(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y);
}

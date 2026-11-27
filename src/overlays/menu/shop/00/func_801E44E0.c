#include "shop_00.h"

MATCH void func_801E44E0(void) {
    g_ShopPanel18Steps[g_UIPanelCurrent->state]();
    func_801E1E80(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy);
}

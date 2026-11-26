#include "shop_00.h"

MATCH void func_801E44E0(void) {
    g_ShopPanel18Steps[g_UiPanelCurrent->state]();
    func_801E1E80(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy);
}

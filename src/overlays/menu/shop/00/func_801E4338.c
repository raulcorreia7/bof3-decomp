#include "shop_00.h"

MATCH void func_801E4338(void) {
    g_ShopPanel16Steps[g_UIPanelCurrent->state]();
    Menu_DrawCuePanel(g_UIPanelCurrent);
}

#include "shop_00.h"

MATCH void func_801E4338(void) {
    g_ShopPanel16Steps[g_MenuCurrentPanel->state]();
    Menu_DrawCuePanel(g_MenuCurrentPanel);
}

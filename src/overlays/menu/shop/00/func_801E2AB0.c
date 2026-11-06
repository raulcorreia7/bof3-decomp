#include "shop_00.h"

MATCH void func_801E2AB0(void) {
    D_801E5DCC[g_MenuCurrentPanel->state]();
    Menu_DrawZennyWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, 0, g_Zenny);
}

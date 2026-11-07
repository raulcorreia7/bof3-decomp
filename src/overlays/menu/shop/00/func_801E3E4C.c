#include "shop_00.h"

/* File-local declarations: the panel handler table selected by panel-task
 * byte 3 and the shop draw helper are owned by this overlay. */

MATCH void func_801E3E4C(void) {
    g_ShopPanel13StateFuncs[g_MenuCurrentPanel->state]();
    Menu_DrawCharacterWindow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_0A, 0, 0);
}

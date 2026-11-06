#include "shop_00.h"

MATCH void func_801E29C8(void) {
    D_801E5DC0[g_MenuCurrentPanel->state]();
    Menu_DrawCommandRow(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_0A,
                        g_MenuCurrentPanel->unk_0B, 0);
}

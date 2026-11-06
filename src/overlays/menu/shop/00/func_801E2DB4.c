#include "shop_00.h"

MATCH void func_801E2DB4(void) {
    D_801E5DF0[g_MenuCurrentPanel->state]();
    Shop_DrawEquipment(g_MenuCurrentPanel->x, g_MenuCurrentPanel->y,
                       g_CharSlot[g_SaveData.walk_order[g_MenuCurrentPanel->unk_0A]]);
}

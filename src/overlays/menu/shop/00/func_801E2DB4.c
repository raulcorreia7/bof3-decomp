#include "shop_00.h"

MATCH void func_801E2DB4(void) {
    g_ShopPanel6StateFuncs[g_MenuCurrentPanel->state]();
    Shop_DrawEquipment(g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y,
                       g_CharSlot[g_PartyFieldOrder[g_MenuCurrentPanel->unk_0A]]);
}

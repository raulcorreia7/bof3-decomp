#include "shop_00.h"

MATCH void func_801D26A8(void) {
    u8* block;
    u8  i;
    u8* state;

    block = Item_GetRecord(g_ShopItemCategory, g_ShopItemId);
    UI_MessageSetVariable(0, 0xC, block);
    D_80148340                = 0x4D;
    g_UIPanelTasks[21].active = 0;
    if (g_PadStates[0].pressed != 0) {
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            if (i == LOB(D_80148656)) {
                g_UIPanelTasks[i + 3].state = 4;
            } else {
                g_UIPanelTasks[i + 3].state = 2;
            }
            i++;
        }
        g_UIPanelTasks[6].state = 1;
        if ((Item_Count(g_ShopItemCategory, g_ShopItemId, 0) & HALF_MASK) != 0) {
            state = &g_MenuStep.state;
            *state -= 2;
        } else {
            state = &g_MenuStep.state;
            *state -= 6;
        }
    }
}

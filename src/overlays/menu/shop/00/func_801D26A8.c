#include "shop_00.h"

MATCH void func_801D26A8(void) {
    u8* block;
    u8  i;
    u8* state;

    block = Item_GetRecord(g_ShopItemCategory, g_ShopItemId);
    TEXT_SetVariable(0, 0xC, block);
    D_80148340 = 0x4D;
    D_80148624 = 0;
    if (g_InputPressed != 0) {
        i = 0;
        while (i < Party_CountOrder(PARTY_ORDER_FIELD)) {
            if (i == LOB(D_80148656)) {
                g_MenuPanelTasks[i + 3].state = 4;
            } else {
                g_MenuPanelTasks[i + 3].state = 2;
            }
            i++;
        }
        D_8014840B = 1;
        if ((Item_Count(g_ShopItemCategory, g_ShopItemId, 0) & HALF_MASK) != 0) {
            state = &D_80148652;
            *state -= 2;
        } else {
            state = &D_80148652;
            *state -= 6;
        }
    }
}

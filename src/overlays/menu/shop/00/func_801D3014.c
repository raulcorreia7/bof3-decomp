#include "shop_00.h"

MATCH void func_801D3014(void) {
    u8*  stock;
    s8*  toggle;
    u16* pad;
    u32  price;
    u8*  counter;
    u32* wallet;

    UI_MessageSetVariable(0, 12, Item_GetRecord(g_ShopItemCategory, g_ShopItemId));
    D_80148340                = 0x52;
    toggle                    = &D_8014865B;
    g_UiPanelTasks[21].active = 1;
    pad                       = &g_PadStates[0].pressed;
    D_80148628                = D_80148334 + (1 - *toggle) * 32 + 0xDE;
    D_8014862A                = g_UiPanelTasks[0].pos.vy + 5;
    if (*pad & (PADLright | PADLleft)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        *toggle ^= 1;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*toggle != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            wallet  = &g_Zenny;
            price   = *wallet + g_ShopItemCount * g_ShopItemPrice;
            *wallet = price;
            if (price > 9999999) {
                *wallet = 9999999;
            }
            stock = g_ItemCategoryCounts[g_ShopItemCategory] + g_ShopStockIndex;
            *stock -= g_ShopItemCount;
            if (g_ItemCategoryCounts[g_ShopItemCategory][g_ShopStockIndex] == 0) {
                g_ItemCategoryIds[g_ShopItemCategory][g_ShopStockIndex]    = 0;
                g_ItemCategoryCounts[g_ShopItemCategory][g_ShopStockIndex] = 0;
            }
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        }
        counter = &D_80148652;
        *counter -= 2;
        return;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_80148652 -= 2;
    }
}

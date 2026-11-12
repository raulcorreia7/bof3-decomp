#include "shop_00.h"

MATCH void func_801D3014(void) {
    u8*  stock;
    s8*  toggle;
    u16* pad;
    u32  price;
    u8*  counter;
    u32* wallet;

    Message_SetVariable(0, 12, Item_GetRecord(g_ShopItemCategory, g_ShopItemId));
    D_80148340 = 0x52;
    toggle     = &D_8014865B;
    D_80148624 = 1;
    pad        = &g_InputPressed;
    D_80148628 = D_80148334 + (1 - *toggle) * 32 + 0xDE;
    D_8014862A = D_80148336 + 5;
    if (*pad & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        *toggle ^= 1;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*toggle != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            wallet  = &g_Zenny;
            price   = *wallet + g_ShopItemCount * g_ShopItemPrice;
            *wallet = price;
            if (price > 9999999) {
                *wallet = 0x98967F;
            }
            stock = D_801C8950[g_ShopItemCategory] + g_ShopStockIndex;
            *stock -= g_ShopItemCount;
            if (D_801C8950[g_ShopItemCategory][g_ShopStockIndex] == 0) {
                D_801C893C[g_ShopItemCategory][g_ShopStockIndex] = 0;
                D_801C8950[g_ShopItemCategory][g_ShopStockIndex] = 0;
            }
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        }
        counter = &D_80148652;
        *counter -= 2;
        return;
    }
    if (*pad & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_80148652 -= 2;
    }
}

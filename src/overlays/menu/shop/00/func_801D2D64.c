#include "shop_00.h"

MATCH void func_801D2D64(void) {
    s32 input;
    u8  previous;

    D_80148340 = 0x51;
    D_80148435 = 1;
    D_80148498 = 1;
    D_80148499 = 7;
    D_8014849A = 0xA;
    D_8014849C = D_80148430;
    D_8014849E = (D_80148432 + (g_ShopStockIndex - D_80148437) * 0xD) + 0x14;
    D_801484A2 = g_ShopItemCategory;
    D_801484A3 = g_ShopItemId;
    D_801484A4 = g_ShopItemCount;
    D_801484A5 = D_801E606C;
    input      = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    previous   = g_ShopItemCount;
    if (input & PADLleft) {
        g_ShopItemCount -= 1;
    } else if (input & PADLright) {
        g_ShopItemCount += 1;
    }
    if ((s8)g_ShopItemCount <= 0) {
        g_ShopItemCount = 1;
    }
    if ((u8)g_ShopItemCountMax < g_ShopItemCount) {
        g_ShopItemCount = g_ShopItemCountMax;
    }
    if (previous != g_ShopItemCount) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    if (input & PADLdown) {
        g_ShopItemCount -= 0xA;
    } else if (input & PADLup) {
        g_ShopItemCount += 0xA;
    }
    if ((s8)g_ShopItemCount <= 0) {
        g_ShopItemCount = 1;
    }
    if ((u8)g_ShopItemCountMax < g_ShopItemCount) {
        g_ShopItemCount = g_ShopItemCountMax;
    }
    if (previous != g_ShopItemCount) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        D_8014865B = 1;
        D_80148652 += 1;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        (*(s8*)&D_80148652)--;
    }
}

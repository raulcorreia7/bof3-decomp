#include "shop_00.h"

MATCH void func_801D2D64(void) {
    s32 input;
    u8  previous;

    D_80148340                = 0x51;
    g_UiPanelTasks[7].unk_09  = 1;
    g_UiPanelTasks[10].active = 1;
    D_80148499                = 7;
    D_8014849A                = 0xA;
    D_8014849C                = g_UiPanelTasks[7].pos.vx;
    D_8014849E                = (D_80148432 + (g_ShopStockIndex - g_UiPanelTasks[7].unk_0B) * 0xD) + 0x14;
    g_UiPanelTasks[10].unk_0A = g_ShopItemCategory;
    g_UiPanelTasks[10].unk_0B = g_ShopItemId;
    g_UiPanelTasks[10].unk_0C = g_ShopItemCount;
    g_UiPanelTasks[10].flags  = D_801E606C;
    input                     = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    previous                  = g_ShopItemCount;
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
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
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
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        D_8014865B = 1;
        D_80148652 += 1;
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        (*(s8*)&D_80148652)--;
    }
}

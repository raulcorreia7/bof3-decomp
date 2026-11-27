#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D1A90(void) {
    s32                     buttons;
    u8                      cursor;
    volatile MenuPanelTask* panel;
    MenuPanelTask*          prev;

    panel         = &g_UIPanelTasks[9];
    prev          = &g_UIPanelTasks[8];
    panel->active = 1;
    D_80148475    = 7;
    D_80148476    = 8;
    D_80148478    = prev->pos.vx;
    D_8014845A    = 1;
    D_8014847F    = g_ShopStockIndex;
    D_80148480    = g_ShopItemCount;
    D_80148494    = D_8018E7CC;
    D_8014847A    = prev->pos.vy + 0x2D;
    D_8014847E    = g_ShopPricePercent;
    D_80148628    = prev->pos.vx + 4;
    D_8014862A    = prev->pos.vy + 0x33;
    D_80148340    = g_ShopItemCount != 0 ? 0x48 : 0x4E;
    buttons       = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    cursor        = g_ShopItemCount;
    if (buttons & PADLleft) {
        g_ShopItemCount = cursor - 1;
    } else if (buttons & PADLright) {
        g_ShopItemCount = cursor + 1;
    }
    if ((s8)g_ShopItemCount <= 0) {
        g_ShopItemCount = 1;
    }
    if ((u8)g_ShopItemCountMax < g_ShopItemCount) {
        g_ShopItemCount = g_ShopItemCountMax;
    }
    if (cursor != g_ShopItemCount) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (buttons & PADLdown) {
        g_ShopItemCount -= 0xA;
    } else if (buttons & PADLup) {
        g_ShopItemCount += 0xA;
    }
    if ((s8)g_ShopItemCount <= 0) {
        g_ShopItemCount = 1;
    }
    if ((u8)g_ShopItemCountMax < g_ShopItemCount) {
        g_ShopItemCount = g_ShopItemCountMax;
    }
    if (cursor != g_ShopItemCount) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (g_ShopItemCount != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            D_8014865B = 1;
            D_80148652 += 1;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_MenuStep.state -= 1;
    }
}
#else
INCLUDE_ASM(func_801D1A90);
#endif

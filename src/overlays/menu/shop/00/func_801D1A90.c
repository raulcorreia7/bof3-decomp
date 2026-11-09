#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D1A90(void) {
    s32            buttons;
    u8             cursor;
    MenuPanelTask* panel;

    panel = &g_MenuPanelTasks[9];
    /* FAKE: the panel store stays above the pad-state read, as retail orders them. */
    FAKE_BARRIER();
    panel->active = 1;
    D_80148475    = 7;
    D_80148476    = 8;
    D_80148478    = panel[-1].pos.x;
    D_8014845A    = 1;
    buttons       = panel[-1].pos.y + 0x2D;
    D_8014847F    = g_ShopStockIndex;
    D_80148480    = g_ShopItemCount;
    D_80148494    = D_8018E7CC;
    D_8014847A    = buttons;
    D_8014847E    = g_ShopPricePercent;
    D_80148628    = panel[-1].pos.x + 4;
    D_8014862A    = panel[-1].pos.y + 0x33;
    D_80148340    = g_ShopItemCount != 0 ? 0x48 : 0x4E;
    buttons       = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
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
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
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
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (g_ShopItemCount != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            D_8014865B = 1;
            g_MenuStep.state += 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        }
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        (*(s8*)&g_MenuStep.state)--;
    }
}
#else
INCLUDE_ASM(func_801D1A90);
#endif

#include "shop_00.h"

MATCH void func_801E09F4(void) {
    s32 raw;
    s32 buttons;
    u16 sum;
    u8  count;
    u8* flag;
    u8  count2;
    u8* flag2;

    D_80148340 = 0x18;
    D_80148628 = D_801483E8 + 5;
    sum        = (D_801483EE << 4) + 0x1A;
    D_8014862A = D_801483EA + sum;
    buttons    = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    if (buttons & PADLup) {
        u8 next;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        next       = D_801483EE - 1;
        D_801483EE = next;
        if ((s8)next < 0) {
            D_801483EE = 2;
        }
    } else if (buttons & PADLdown) {
        u8 next;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        next       = D_801483EE + 1;
        D_801483EE = next;
        if ((next & BYTE_MASK) >= 3U) {
            D_801483EE = 0;
        }
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        raw = D_801483EE & BYTE_MASK;
        if (raw == 0) {
            flag       = &D_80148652;
            count      = *flag;
            D_801483EF = D_801483EE;
            *flag      = count + 1;
            return;
        }
        Menu_RunAbilityStockSort(raw);
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        flag2                = &D_80148651;
        D_801483E4           = 0;
        count2               = *flag2;
        g_BattleMessageState = 4;
        *flag2               = count2 - 2;
    }
}

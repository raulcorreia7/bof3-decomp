#include "shop_00.h"

/* nonmatching unmeasured: tried the first draft cleaned with a byte cursor and typed cell table. resume: close the
 * +0x14 prologue store order (s2 frame). */
#ifdef NON_MATCHING
NON_MATCHING void func_801E032C(void) {
    s32 input;
    u8* cell;
    s8  previous;

    cell       = &g_Characters[D_801483A6].abilities.skill[D_801483A7];
    D_80148340 = *(s16*)(D_801CA71E + *cell * 0x14);
    if (D_8014839F == 0) {
        D_80148624 = 1;
        D_80148628 = D_801483A0 + 7;
        D_8014862A = D_801483A2 + D_801483A7 * 0xD + 0x1A;
    } else {
        D_80148624 = 0;
    }
    previous = D_801483A7;
    input    = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    if (input & PADLup) {
        D_801483A7 -= 1;
        if (D_801483A7 & 0x80) {
            D_801483A7 = 0;
        }
    } else if (input & PADLdown) {
        D_801483A7 += 1;
        if ((u8)D_801483A7 >= 0xA) {
            D_801483A7 = 9;
        }
    }
    if (previous != D_801483A7) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    D_801483A8 = 0xFF;
    cell       = &g_Characters[D_801483A6].abilities.skill[D_801483A7];
    if (g_InputMasks[MENU_INPUT_CONFIRM] & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        D_801483A8 = (u8)D_801483A7;
        g_MenuStep.state += 1;
        return;
    }
    if (g_InputPressed & PADRleft) {
        if (*cell != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            Char_AddAbility(*cell, 0, 1, 0);
            *cell = 0;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        return;
    }
    if (g_InputMasks[MENU_INPUT_CANCEL] & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_8014837B           = 2;
        D_8014839F           = 4;
        D_801483A8           = 0xFF;
        g_BattleMessageState = 1;
        g_MenuStep.state -= 1;
    }
}
#else
INCLUDE_ASM(func_801E032C);
#endif

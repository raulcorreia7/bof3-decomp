#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E032C(void) {
    s32 input;
    s32 row;
    u8* cell;
    u8* entry;
    u8* cursor;
    u8* index;
    u8* step;
    u8  previous;
    s8  next;

    entry      = (u8*)&g_Characters[D_801483A6] + DECOMP_OFFSETOF(Character, abilities.skill) + D_801483A7;
    D_80148340 = g_Abilities[*entry].description;
    if (D_8014839F == 0) {
        D_80148624 = 1;
        D_80148628 = D_801483A0 + 7;
        row        = D_801483A7 * 0xD + 0x1A;
        D_8014862A = D_801483A2 + row;
    } else {
        D_80148624 = 0;
    }
    input    = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    cursor   = &D_801483A7;
    previous = *cursor;
    if (input & PADLup) {
        next    = previous - 1;
        *cursor = next;
        if (next < 0) {
            *cursor = 0;
        }
    } else if (input & PADLdown) {
        next    = previous + 1;
        *cursor = next;
        if ((u8)next >= 0xA) {
            *cursor = 9;
        }
    }
    index = &D_801483A7;
    if (previous != *index) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    D_801483A8 = 0xFF;
    cell       = (u8*)&g_Characters[D_801483A6] + DECOMP_OFFSETOF(Character, abilities.skill) + *index;
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        step       = &D_80148652;
        D_801483A8 = *index;
        *step += 1;
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
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_8014837B           = 2;
        D_8014839F           = 4;
        D_801483A8           = 0xFF;
        g_BattleMessageState = 1;
        D_80148652 -= 1;
    }
}
#else
INCLUDE_ASM(func_801E032C);
#endif

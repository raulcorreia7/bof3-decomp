#include "battle_15.h"

#ifdef NON_MATCHING
NON_MATCHING void func_80099364(void) {
    u8* state;
    u8* panel;
    u16 held;
    state                                    = (u8*)&D_8014862E;
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Message_GetText((*state) == 0u ? 0x2Fu : 0x31u);
    if (D_80148627 == 0u) {
        D_801485DC = 1u;
        D_801485E0 = D_80148628 + (6 * (8 * (*state)));
        D_801485E2 = D_8014862A + 4u;
    } else {
        D_801485DC = 0u;
    }
    panel  = (u8*)&D_8014862F;
    *panel = 0xFFu;
    held   = g_InputPressed;
    if ((held & (PADLright | PADLleft)) != 0u) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_8014862E ^= 1u;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        D_80148624              = 0u;
        D_801483C0              = 1u;
        g_Battle.phase.sub_step = 2u;
        g_Battle.ui_step        = 1u;
    } else if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        *panel = D_8014862E;
        if (D_8014862E == 0u) {
            func_8009B160();
            g_Battle.ui_state += 3u;
        } else {
            func_8009B03C();
            D_8014859D = g_BattleItemRow;
            D_801485A0 = D_801485C4;
            g_Battle.ui_state += 1u;
        }
    } else if ((held & PADLdown) != 0u) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        D_80148624              = 0u;
        D_801483C0              = 1u;
        g_Battle.phase.sub_step = 2u;
        g_Battle.ui_step        = 1u;
    }
}
#else
INCLUDE_ASM(func_80099364);
#endif

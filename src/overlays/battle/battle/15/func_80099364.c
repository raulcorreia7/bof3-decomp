#include "battle_15.h"

/* nonmatching 61.07%: tried ternary polarity; panel s1 local sunk to first use (59.23% -> 61.07%); frame/saved-reg set
 * matched; a 3x10min search over source rewrites (best 70.54% with a private unsigned char D_801485E0 extern that
 * narrows battle_15.h's volatile u16; dropped: retail stores halfwords at 0x801485E0/E2 (sh at
 * +0x80099400/+0x8009940c), so that form breaks behavior); a register pin on flag (a0/v0) had no effect at the residual
 * site. a second search (15min, 263k rewrites) from this draft: best 75.00% (99/132, +12), residual moves to +0x00c8
 * opcode (lhu v0,0(s0) vs li v0,255 shape); non-exact and not adopted pending a clean-C89 restatement. resume: restate
 * the rank-1 form as clean C89 and attack the +0x00c8 hunk, or the register-pair form that loads D_80148627 after the
 * D_801EB5B4 store (retail order +0x003c..0x0064), or an approved register pin targeting the s1-setup hoist. */
#ifdef NON_MATCHING
NON_MATCHING void func_80099364(void) {
    u8* state;
    u8* panel;
    u16 held;
    state                                    = (u8*)&D_8014862E;
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Resource_GetText((*state) == 0u ? 0x2Fu : 0x31u);
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
        SND_PlayCue(EMI_CUE_ID(1, 1));
        D_8014862E ^= 1u;
    }
    if ((held & g_InputMasks[INPUT_SLOT_CANCEL]) != 0u) {
        D_80148624      = 0u;
        D_801483C0      = 1u;
        g_BattleSubStep = 2u;
        g_BattleUIStep  = 1u;
    } else if ((held & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0u) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        *panel = D_8014862E;
        if (D_8014862E == 0u) {
            func_8009B160();
            g_BattleUIState += 3u;
        } else {
            func_8009B03C();
            D_8014859D = g_BattleItemRow;
            D_801485A0 = D_801485C4;
            g_BattleUIState += 1u;
        }
    } else if ((held & PADLdown) != 0u) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        D_80148624      = 0u;
        D_801483C0      = 1u;
        g_BattleSubStep = 2u;
        g_BattleUIStep  = 1u;
    }
}
#else
INCLUDE_ASM(func_80099364);
#endif

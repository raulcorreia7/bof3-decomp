#include "magic080_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EECE4};

    table[SP_REF(u8*, 0x44)[1]]();
}

/* Scheduling and regalloc residual: the target-Y load stays above the coord_x store while retail
 * pins it below, and the spad pointer and target-X swap v0/v1 (first difference lui v1,0x1f80 at
 * 0x801EEC5C); plain, saved-target and hybrid target forms all give the same schedule. */
INCLUDE_ASM(func_801EEC5C);

/* The two handlers read the variant byte already loaded in a0, so the calls pass no argument: a
 * call with an argument adds a zero-extension the retail code folds away. */
MATCH void func_801EECE4(void) {
    u8 temp_a0;
    u8 temp_v0;

    func_800AF764();
    temp_a0 = g_SpadWork->word_08.byte.unk_0B;
    g_SpadWork->unk_2E.half -= 0x24;
    if (temp_a0 != 0) {
        func_801EEF5C();
    } else {
        func_801EED94();
    }
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EED94);

INCLUDE_ASM(func_801EEF5C);

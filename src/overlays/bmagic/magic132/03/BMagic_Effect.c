#include "magic132_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EEDD0);

INCLUDE_ASM(func_801EEEF4);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

INCLUDE_ASM(func_801EF0A4);

MATCH void func_801EF114(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF158);

INCLUDE_ASM(func_801EF200);

MATCH void func_801EF324(void) {
    PartyBattler* work;
    u8            count;

    work                      = g_SpadWork;
    count                     = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = count;
    work->coord_x_34.raw += work->unk_0C;
    work->coord_y_38.raw += work->unk_10;
    if (count == 0) {
        g_SpadWork->unk_02++;
    }
}

MATCH void func_801EF388(void) {
    s32 temp_v0;

    g_SpadWork->word_08.byte.unk_0B = (g_SpadWork->word_08.byte.unk_0B - 1) & 0x3F;
    temp_v0                         = g_SpadWork->unk_1C + 2;
    g_SpadWork->unk_1C              = temp_v0;
    if (temp_v0 == 0x80) {
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF3E0);

MATCH void func_801EF44C(void) {
    g_SpadWork->unk_1C -= 1;
    g_SpadWork->unk_20 -= 2;
    if (g_SpadWork->unk_1C == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF4A4);

INCLUDE_ASM(func_801EF5B0);

INCLUDE_ASM(func_801EF914);

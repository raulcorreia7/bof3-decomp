#include "magic042_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Bmagic_DispatchTaskPair(func_801EEC70, func_801EED44);
}

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

MATCH void func_801EEDA4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EEDE8);

MATCH void func_801EEF08(void) {
    g_Task->word_08.byte.facing_08 = D_801EB4E0->word_08.byte.facing_08;
    g_Task->coord_x_34.raw         = D_801EB4E0->coord_x_34.raw;
    g_Task->coord_y_38.raw         = D_801EB4E0->coord_y_38.raw;
    g_Task->word_3C.word           = D_801EB4E0->word_3C.word;
    func_801EF1B0();
    g_Task->word_08.byte.unk_0B   = 0;
    g_Task->word_08.byte.unk_09   = 0;
    g_Task->word_08.byte.timer_0A = 0;
    g_Task->step += 1;
}

MATCH void func_801EEFB8(void) {
    PartyBattler* work;

    work = g_Task;
    work->word_08.byte.unk_0B++;
    work = g_Task;
    work->word_08.byte.timer_0A++;
    if (work->word_08.byte.timer_0A == 4) {
        work = g_Task;
        work->step++;
    }
}

MATCH void func_801EF024(void) {
    PartyBattler* work;

    work = g_Task;
    work->word_08.byte.unk_0B++;
    work = g_Task;
    work->word_08.byte.unk_09 += 8;
    if (work->word_08.byte.unk_09 == 80) {
        work = g_Task;
        work->step++;
    }
}

MATCH void func_801EF090(void) {
    u8 timer;

    g_Task->word_08.byte.unk_0B += 1;
    g_Task->word_08.byte.unk_09 += 4;
    timer                         = g_Task->word_08.byte.timer_0A + 4;
    g_Task->word_08.byte.timer_0A = timer;
    if ((timer & 0xFF) == 0x20) {
        g_Task->step += 1;
    }
}

MATCH void func_801EF118(void) {
    u8 temp_v0;
    u8 temp_v0_2;

    g_Task->word_08.byte.unk_0B += 1;
    temp_v0 = g_Task->word_08.byte.unk_09;
    if (temp_v0 != 0) {
        g_Task->word_08.byte.unk_09 = temp_v0 - 0xC;
    }
    temp_v0_2                     = g_Task->word_08.byte.timer_0A - 4;
    g_Task->word_08.byte.timer_0A = temp_v0_2;
    if (!(temp_v0_2 & 0xFF)) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF1B0);

INCLUDE_ASM(func_801EF380);

INCLUDE_ASM(func_801EF71C);

INCLUDE_ASM(func_801EF920);

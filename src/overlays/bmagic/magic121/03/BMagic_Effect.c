#include "magic121_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEE08};
    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEE68(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEEAC);

INCLUDE_ASM(func_801EF03C);

MATCH void func_801EF218(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 8;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 32) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF268(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_0B + 1;
    g_SpadWork->word_08.byte.unk_0B = timer;
    if (timer == 8) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF2D4(void) {
    u8 timer;

    timer              = g_SpadWork->unk_04 + 2;
    g_SpadWork->unk_04 = timer;
    if (timer == 16) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF324(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (++work->unk_0C == 0x2E) {
        work->unk_02++;
    }
}

MATCH void func_801EF35C(void) {
    u8 timer;

    timer              = g_SpadWork->unk_04 - 2;
    g_SpadWork->unk_04 = timer;
    if (timer == 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF3A8);

/* resume: best 368/865 instructions differ (size 0xDCC vs 0xD84; the ternary tpage form, prologue and loop head are exact); first mismatch +0x80 (sp20 = 0 sinks past the y load and sp18 = 1 fills the skip-branch delay slot); next lever: one prim cursor pseudo created before the five cell derivations so they take s1-s4/s7 as retail does, then the permuter. */
INCLUDE_ASM(func_801EF414);

INCLUDE_ASM(func_801F0198);

INCLUDE_ASM(func_801F06E8);

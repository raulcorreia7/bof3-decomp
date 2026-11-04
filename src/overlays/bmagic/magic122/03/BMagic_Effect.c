#include "magic122_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDFC};
    SYS_DISPATCH_TASK(handlers, 1, g_SpadWork);
}

INCLUDE_ASM(func_801EEC5C);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEE5C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEEA0);

INCLUDE_ASM(func_801EEF2C);

MATCH void func_801EF158(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_0A += 3;
    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    if (work->word_08.byte.unk_09 == 8) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801EF1C4(void) {
    PartyBattler* work;
    u8            timer;

    work                      = g_SpadWork;
    work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
    work                      = g_SpadWork;
    timer                     = work->word_08.byte.unk_09 + 1;
    work->word_08.byte.unk_09 = timer;
    if (timer == 24) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        work         = g_SpadWork;
        work->unk_02 = work->unk_02 + 1;
    }
}

MATCH void func_801EF24C(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 120) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801EF29C);

INCLUDE_ASM(func_801EF324);

INCLUDE_ASM(func_801EFBA8);

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
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEDE8);

INCLUDE_ASM(func_801EEF08);

MATCH void func_801EEFB8(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_0B++;
    work = g_SpadWork;
    work->word_08.byte.unk_0A++;
    if (work->word_08.byte.unk_0A == 4) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

MATCH void func_801EF024(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_0B++;
    work = g_SpadWork;
    work->word_08.byte.unk_09 += 8;
    if (work->word_08.byte.unk_09 == 80) {
        work = g_SpadWork;
        work->unk_02++;
    }
}

INCLUDE_ASM(func_801EF090);

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF1B0);

INCLUDE_ASM(func_801EF380);

INCLUDE_ASM(func_801EF71C);

INCLUDE_ASM(func_801EF920);

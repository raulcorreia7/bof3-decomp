#include "magic075_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EEDE0);

INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFF4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
}

INCLUDE_ASM(func_801EF038);

INCLUDE_ASM(func_801EF0D0);

MATCH void func_801EF2A8(void) {
    PartyBattler* work;

    if (func_8014DAEC() != 0u) {
        work                      = (PartyBattler*)D_801EB4E0;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B + 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF2F4);

INCLUDE_ASM(func_801EF500);

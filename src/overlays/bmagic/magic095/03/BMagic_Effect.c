#include "magic095_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC18);

INCLUDE_ASM(func_801EEC9C);

INCLUDE_ASM(func_801EEE60);

INCLUDE_ASM(func_801EEF64);

MATCH void func_801EEFFC(void) {
    u8 timer;

    func_801EF1FC();
    func_801EF804();
    func_801EFDDC();
    timer              = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

MATCH void func_801EF070(void) {
    u8            timer;
    u32           slot;
    u8*           selector;
    PartyBattler* battler;

    func_801EFDDC();
    timer              = g_SpadWork->unk_0A - 1;
    g_SpadWork->unk_0A = timer;
    if (timer == 0) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1FC);

INCLUDE_ASM(func_801EF804);

INCLUDE_ASM(func_801EFDDC);

INCLUDE_ASM(func_801F0018);

INCLUDE_ASM(func_801F0070);

INCLUDE_ASM(func_801F00D8);

INCLUDE_ASM(func_801F012C);

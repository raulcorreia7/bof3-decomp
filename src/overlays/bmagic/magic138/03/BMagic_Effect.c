#include "magic138_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EED60);

INCLUDE_ASM(func_801EEED8);

MATCH void func_801EEF60(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEFA4);

INCLUDE_ASM(func_801EF04C);

INCLUDE_ASM(func_801EF3A0);

MATCH void func_801EF50C(void) {
    func_801E5988();
}

INCLUDE_ASM(func_801EF52C);

INCLUDE_ASM(func_801EF5D0);

MATCH void func_801EF6A4(void) {
    if (func_8014D978() != 0u) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    } else {
        Area_AddActor();
    }
}

MATCH void func_801EF6F8(void) {
    PartyBattler* active;

    active = BATTLE_ACTIVE_WORK;
    active->word_08.byte.unk_0B--;
    func_801E5988();
}

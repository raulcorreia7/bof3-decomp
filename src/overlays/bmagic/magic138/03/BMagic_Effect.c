#include "magic138_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EED60);

MATCH void func_801EEED8(void) {
    PartyBattler* saved_work;

    saved_work = g_SpadWork;
    g_SpadWork = D_801EB4E0;
    func_8014D978();
    g_SpadWork = saved_work;
    if (saved_work->word_08.byte.unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= 4;
        func_801E5988();
    }
}

MATCH void func_801EEF60(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_SpadWork->step_01);
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

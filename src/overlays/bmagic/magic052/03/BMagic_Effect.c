#include "magic052_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EEC7C(void) {
    PartyBattler* work;

    g_SpadWork->word_08.byte.unk_09 = 8;
    g_SpadWork->word_08.byte.unk_0A = 4;
    work                            = g_SpadWork;
    work->step_01                   = work->step_01 + 1;
}

INCLUDE_ASM(func_801EECBC);

MATCH void func_801EEE30(void) {
    if (g_SpadWork->word_08.byte.unk_0A-- == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EEE94(void) {
    Callback handlers[2];

    handlers[0] = func_801EEEE0;
    handlers[((u8*)g_SpadWork)[1]]();
}

INCLUDE_ASM(func_801EEEE0);

INCLUDE_ASM(func_801EEF84);

MATCH void func_801EF070(void) {
    PartyBattler* work;

    if (func_8014D978() != 0u) {
        work         = g_SpadWork;
        work->unk_02 = work->unk_02 + 1;
    } else {
        Area_AddActor();
    }
}

MATCH void func_801EF0C4(void) {
    func_801E5988();
}

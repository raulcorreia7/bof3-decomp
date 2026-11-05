#include "magic010_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    BattleResultRings table = D_801EEC04;

    table.handlers[SP_REF(PartyBattler*, 0x44u)->step_01]();
}

MATCH void func_801EEC80(void) {
    PartyBattler** actor;

    actor = &g_BattleSelectedActor;
    func_80196718(*actor);
    g_SpadWork->word_08.byte.unk_0B = func_8019651C(*actor, 0, 0, 0, 1);
    g_SpadWork->word_08.byte.unk_09 = 0;
    g_SpadWork->step_01 += 1;
}

INCLUDE_ASM(func_801EED0C);

INCLUDE_ASM(func_801EEE20);

#include "shared/Effect_PlayOnce.h"

#include "magic010_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    BattleResultRings table = D_801EEC04;

    table.handlers[SP_REF(PartyBattler*, 0x44u)->step_01]();
}

#include "overlays/bmagic/Effect_SelectTargetAndAdvance.h"

INCLUDE_ASM(func_801EED0C);

INCLUDE_ASM(func_801EEE20);

#include "shared/Effect_PlayOnce.h"

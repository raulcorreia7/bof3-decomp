#include "magic166_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_MarkDamagedOnZeroTick);

    BMAGIC_RUN_EFFECT_SLOTS(D_801EF724, BMagic_DispatchEffectMode);
}

#include "overlays/bmagic/shared/func_801EED04.h"

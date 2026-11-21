#include "magic166_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_MarkDamagedOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EF724[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EF724[i];
            g_BattleEffectBattler = D_801EF724[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

#include "overlays/bmagic/shared/func_801EED04.h"

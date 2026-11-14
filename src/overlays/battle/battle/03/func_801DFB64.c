#include "battle_03.h"

MATCH void func_801DFB64(void) {
    volatile u16* gate;
    u16           half;

    if (Battle_IsPartyMemberBlocked() != 0u) {
        gate = &g_Battle.state;
        if ((*gate & BATTLE_STATE_CRITICAL) != 0u) {
            Battle_AllocEffect(0, 2);
        }
        Battle_MarkDamaged(g_Battle.target_selector);
        half        = (*gate | BATTLE_STATE_EFFECT_PLAYING);
        *(u16*)gate = half;
        func_801E1DD4();
    }
}

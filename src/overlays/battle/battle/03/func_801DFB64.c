#include "battle_03.h"

MATCH void func_801DFB64(void) {
    volatile u16* gate;
    u16           half;

    if (func_801DEE4C() != 0u) {
        gate = &g_BattleState;
        if ((*gate & BATTLE_STATE_CRITICAL) != 0u) {
            Battle_AllocEffect(0, 2);
        }
        func_800A9820(g_BattleTargetSelector);
        half        = (*gate | BATTLE_STATE_EFFECT_PLAYING);
        *(u16*)gate = half;
        func_801E1DD4();
    }
}

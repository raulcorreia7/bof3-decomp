#include "battle_03.h"

MATCH void func_801E2120(void) {
    volatile PartyBattler* work;
    volatile u16*          gate;
    u16                    half;

    work = g_Task;
    if ((work->header.flags & ACTOR_FLAG_HIDDEN) == 0u) {
        gate        = &g_BattleState;
        half        = (*gate | BATTLE_STATE_EFFECT_PLAYING);
        *(u16*)gate = half;
        func_801E1DD4();
    }
}

#include "area108_14.h"

MATCH void func_801F3C84(void) {
    PartyBattler* saved;
    Actor*        actor;
    PartyBattler* battler;
    u8            i;
    u8            j;

    saved = (PartyBattler*)g_Task;
    for (i = 0; i < ACTOR_COUNT; i++) {
        actor = &g_Actors[i];
        TASK_SET(actor);
        if (actor->header.flags & 1) {
            actor->unk_29 = 5;
            func_8014D290();
        }
    }
    for (j = 0; j < g_PartySize; j++) {
        battler = &g_BattlePartyBattlers[j];
        TASK_SET(battler);
        battler->unk_29 = 5;
        func_8014D290();
    }
    TASK_SET(saved);
}

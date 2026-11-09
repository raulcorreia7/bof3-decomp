#include "boss017_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    /* FAKE: retail reads D_800C1A70 as u8[]. */
    EnemyBattler_SetScript(work, ((u8*)&D_800C1A70), func_800C1964, D_800C1A94);
    ACTOR_SET_MODE(2);
    Actor_StepAnimLoop();
}

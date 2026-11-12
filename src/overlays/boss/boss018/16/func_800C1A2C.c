#include "boss018_16.h"

MATCH void func_800C1A2C(void) {
    EnemyBattler* work;

    if (SYS_TestFlag(g_SceneFlags, 54) != 0) {
        g_BattleCurrentEnemy->hp = D_801FD700;
        g_BattleCurrentEnemy->ap = D_801FD6FE;
    } else {
        SYS_SetFlag(g_SceneFlags, 54);
    }
    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C2C44, func_800C1B18, D_800C2C94);
    ACTOR_SET_MODE(1);
    Actor_RequestScript(2);
    Actor_StepAnimLoop();
}

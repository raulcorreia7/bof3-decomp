#include "boss018_16.h"

MATCH void func_800C1890(void) {
    EnemyBattler* work;

    if (SYS_TestFlag(g_SceneFlags, 53) != 0) {
        g_BattleCurrentEnemy->hp = D_801FD700;
        g_BattleCurrentEnemy->ap = D_801FD6FE;
    } else {
        SYS_SetFlag(g_SceneFlags, 53);
    }
    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C2C38, func_800C197C, D_800C2C8C);
    ACTOR_SET_MODE(1);
    Actor_RequestScript(2);
    Actor_StepAnimLoop();
}

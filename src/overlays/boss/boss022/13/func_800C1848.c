#include "boss022_13.h"
#include "area/spad.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1B18, func_800C19B8, D_800C1B24);
    ACTOR_SET_MODE(1);
    Area_SelectSceneRecord(0x153);
    g_Task->unk_2A = 0;
    Actor_SelectScript(0);
}

#include "boss022_13.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1B18;
    work->unk_E4 = func_800C19B8;
    work->unk_E8 = D_800C1B24;
    ACTOR_SET_STEP(1);
    Area_FindSceneRecord(0x153);
    SPAD_WORK_BYTES[0x2A] = 0;
    Actor_SelectScript(0);
}

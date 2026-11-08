#include "boss002_16.h"

MATCH void func_800C1A00(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    if (work->hp == 0xFFFF) {
        g_Battle.action_type = 3;
        TASK_BYTES[4]        = 0;
        SND_QueueSelectionFx(0x602);
    }
}

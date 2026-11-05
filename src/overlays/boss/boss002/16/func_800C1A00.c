#include "boss002_16.h"

MATCH void func_800C1A00(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    if (work->hp_94 == 0xFFFF) {
        g_BattleActionType = 3;
        SPAD_WORK_BYTES[4] = 0;
        SND_QueueSelectionFx(0x602);
    }
}

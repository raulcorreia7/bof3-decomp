#include "boss002_16.h"

MATCH void func_800C1A00(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    if (work->hp == 65535) {
        g_Battle.action_type = 3;
        SELF(Actor)->unk_04  = 0;
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_ENEMY, 2));
    }
}

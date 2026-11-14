#include "boss018_16.h"

MATCH void func_800C20BC(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    if (work->turn.hp_change > 0) {
        SND_QueueSelectionEffect((RANDOM_MASK(1)) ? 0x600 : 0x601);
    }
}

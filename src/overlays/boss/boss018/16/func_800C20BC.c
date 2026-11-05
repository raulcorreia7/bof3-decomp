#include "boss018_16.h"

MATCH void func_800C20BC(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    if (work->damage > 0) {
        SND_QueueSelectionFx((rand() & 1) ? 0x600 : 0x601);
    }
}

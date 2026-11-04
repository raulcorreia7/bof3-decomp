#include "boss008_16.h"

MATCH void func_800C1EF4(void) {
    EnemyBattler* work;

    work                = g_BattleCurrentEnemy;
    work->script        = D_800C264C;
    work->unk_E4        = func_800C1F4C;
    work->unk_E8        = D_800C2658;
    g_SpadWork->step_01 = 2;
    func_8014D978();
}

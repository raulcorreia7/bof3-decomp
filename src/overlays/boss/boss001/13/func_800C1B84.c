#include "boss001_13.h"

MATCH void func_800C1B84(void) {
    EnemyBattler* work;

    work                = g_BattleCurrentEnemy;
    work->script        = D_800C2194;
    work->unk_E4        = func_800C1E00;
    work->unk_E8        = D_800C21B4;
    g_SpadWork->step_01 = 2;
    func_8014D978();
}

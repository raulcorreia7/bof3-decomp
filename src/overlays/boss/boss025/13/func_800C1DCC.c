#include "boss025_13.h"

MATCH void func_800C1DCC(void) {
    EnemyBattler* work;

    work                = g_BattleCurrentEnemy;
    work->script        = D_800C3180;
    work->unk_E4        = func_800C20F0;
    work->unk_E8        = D_800C3194;
    g_Task->facing      = 3;
    g_Task->header.mode = 2;
    func_8014D978();
}

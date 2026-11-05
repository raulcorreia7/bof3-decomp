#include "boss001_13.h"

MATCH void func_800C1864(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C217C;
    work->unk_E4 = func_800C1AF0;
    work->unk_E8 = D_800C21AC;
    g_Task->mode = 2;
    func_8014D978();
}

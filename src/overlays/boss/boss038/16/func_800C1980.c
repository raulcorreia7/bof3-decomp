#include "boss038_16.h"

MATCH void func_800C1980(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1C10;
    work->unk_E4 = func_800C19E4;
    work->flags_104 |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8        = D_800C1C1C;
    g_SpadWork->step_01 = 2;
    func_8014D978();
}

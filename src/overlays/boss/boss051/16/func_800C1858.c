#include "boss051_16.h"

MATCH void func_800C1858(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1DB0;
    work->unk_E4 = func_800C19C4;
    work->action_flags |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C1DBC;
    g_Task->mode = 2;
    func_8014D978();
}

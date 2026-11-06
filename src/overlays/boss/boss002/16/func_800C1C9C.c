#include "boss002_16.h"

MATCH void func_800C1C9C(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1F9C;
    work->unk_E4 = func_800C1D00;
    work->action_flags |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C1FB4;
    ACTOR_SET_MODE(2);
    func_8014D978();
}

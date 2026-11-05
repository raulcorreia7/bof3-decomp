#include "boss035_16.h"

MATCH void func_800C1994(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1D10;
    work->unk_E4 = func_800C19F8;
    work->action_flags |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C1D24;
    ACTOR_SET_STEP(2);
    func_8014D978();
}

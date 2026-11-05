#include "boss036_16.h"

MATCH void func_800C1CDC(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C2020;
    work->unk_E4 = func_800C1D40;
    work->action_flags |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C202C;
    ACTOR_SET_STEP(2);
    func_8014D978();
}

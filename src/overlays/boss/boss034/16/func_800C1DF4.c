#include "boss034_16.h"

MATCH void func_800C1DF4(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C26B8;
    work->unk_E4 = func_800C1E58;
    work->action_flags |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C26C4;
    ACTOR_SET_MODE(2);
    func_8014D978();
}

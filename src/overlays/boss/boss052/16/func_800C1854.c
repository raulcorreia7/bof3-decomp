#include "boss052_16.h"

MATCH void func_800C1854(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1F3C;
    work->unk_E4 = func_800C1984;
    work->action_flags |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C1F48;
    ACTOR_SET_MODE(2);
    func_8014D978();
}

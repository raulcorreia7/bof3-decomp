#include "boss035_16.h"

MATCH void func_800C1A98(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1D04;
    work->unk_E4 = func_800C1AFC;
    work->turn.action_flags.value |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C1D1C;
    ACTOR_SET_MODE(2);
    func_8014D978();
}

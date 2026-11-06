#include "boss032_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1C2C;
    work->unk_E4 = func_800C1978;
    work->turn.action_flags.value |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C1C38;
    ACTOR_SET_MODE(2);
    func_8014D978();
}

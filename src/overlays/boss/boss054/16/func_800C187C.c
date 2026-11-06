#include "boss054_16.h"

MATCH void func_800C187C(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C2078;
    work->unk_E4 = func_800C18E0;
    work->turn.action_flags.value |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C2084;
    ACTOR_SET_MODE(2);
    func_8014D978();
}

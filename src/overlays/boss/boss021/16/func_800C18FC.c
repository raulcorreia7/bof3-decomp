#include "boss021_16.h"
#include "area/spad.h"

MATCH void func_800C18FC(void) {
    EnemyBattler* work;

    Actor_RequestScript(4);
    ((Actor*)g_Task)->unk_2A = 0;
    Actor_StepAnimOnce();
    Battle_DefeatEnemy();
    work = g_BattleCurrentEnemy;
    work->turn.damage_flags.value |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    ACTOR_SET_MODE(3);
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}

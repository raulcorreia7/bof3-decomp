#include "battle_03.h"

MATCH void func_801E5B8C(void) {
    BattleEffectStage1Steps table;

    table = g_BattleEffectStage1Steps;
    table.steps[D_801EC2E0->step_index]();
}

#include "battle_03.h"

MATCH void func_801E5C1C(void) {
    BattleEffectStage3Steps handlers;

    handlers = g_BattleEffectStage3Funcs;
    handlers.steps[D_801EC2E0->step_index]();
}

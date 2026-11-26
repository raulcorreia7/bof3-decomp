#include "battle_03.h"

/* func_801E5C1C */
MATCH void Battle_RunBossEffect(void) {
    BattleBossEffectSteps handlers;

    handlers = g_BattleBossEffectSteps;
    handlers.steps[D_801EC2E0->effect_type]();
}

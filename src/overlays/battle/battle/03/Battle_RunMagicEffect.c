#include "battle_03.h"

/* func_801E5B8C */
MATCH void Battle_RunMagicEffect(void) {
    BattleMagicEffectSteps table;

    table = g_BattleMagicEffectSteps;
    table.steps[D_801EC2E0->effect_type]();
}

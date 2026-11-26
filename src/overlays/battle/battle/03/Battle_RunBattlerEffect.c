#include "battle_03.h"

/* func_801E5AF4 */
MATCH void Battle_RunBattlerEffect(void) {
    BattleBattlerEffectSteps table = g_BattleBattlerEffectSteps;

    table.steps[D_801EC2E0->effect_type]();
}

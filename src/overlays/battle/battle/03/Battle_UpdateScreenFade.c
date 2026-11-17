#include "battle_03.h"

/* func_801E6930 */
MATCH void Battle_UpdateScreenFade(void) {
    BattleScreenFadeSteps handlers;

    handlers = g_BattleScreenFadeSteps;
    handlers.steps[((u8*)(D_801EC2E0))[1]]();
}

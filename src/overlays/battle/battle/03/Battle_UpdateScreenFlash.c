#include "battle_03.h"

/* func_801E63C0 */
MATCH void Battle_UpdateScreenFlash(void) {
    BattleScreenFlashSteps handlers;

    handlers = g_BattleScreenFlashSteps;
    handlers.steps[((u8*)(D_801EC2E0))[1]]();
}

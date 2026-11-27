#include "battle_15.h"

MATCH void func_800B0CE4(void) {
    BattleMenuPanel2Steps handlers;

    handlers = D_80096A14;
    handlers.steps[g_UIPanelCurrent->state]();
}

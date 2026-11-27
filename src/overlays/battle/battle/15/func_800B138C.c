#include "battle_15.h"

MATCH void func_800B138C(void) {
    BattleMenuPanel3Steps handlers;

    handlers = D_80096A34;
    handlers.steps[g_UIPanelCurrent->state]();
}

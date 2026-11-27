#include "battle_15.h"

MATCH void func_800B01F0(void) {
    BattleMenuPanel0Steps handlers;

    handlers = D_800969F8;
    handlers.steps[g_UIPanelCurrent->state]();
}

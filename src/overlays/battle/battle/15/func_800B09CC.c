#include "battle_15.h"

MATCH void func_800B09CC(void) {
    BattleMenuPanel1Steps handlers;

    handlers = D_80096A08;
    handlers.steps[g_UIPanelCurrent->state]();
}

#include "battle_15.h"

MATCH void func_800B155C(void) {
    BattleMenuPanel4Steps handlers;

    handlers = D_80096A40;
    handlers.steps[g_UIPanelCurrent->state]();
}

#include "battle_03.h"

MATCH void func_801E94D0(void) {
    BattlePanel3Steps handlers;

    handlers = D_801D0FC4;
    handlers.steps[BATTLE_PANEL_TASK->state]();
}

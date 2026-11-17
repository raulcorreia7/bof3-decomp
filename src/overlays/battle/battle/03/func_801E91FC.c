#include "battle_03.h"

MATCH void func_801E91FC(void) {
    BattlePanel1Steps handlers;

    handlers = D_801D0FAC;
    handlers.steps[BATTLE_PANEL_TASK->state]();
}

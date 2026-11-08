#include "battle_03.h"

MATCH void func_801E91FC(void) {
    BattlePanel1States handlers;

    handlers = D_801D0FAC;
    handlers.states[BATTLE_PANEL_TASK->state]();
}

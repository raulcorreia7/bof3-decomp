#include "battle_03.h"

MATCH void func_801E943C(void) {
    BattlePanel2States handlers;

    handlers = D_801D0FB8;
    handlers.states[BATTLE_PANEL_TASK->state]();
}

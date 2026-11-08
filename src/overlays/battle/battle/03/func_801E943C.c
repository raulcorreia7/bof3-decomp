#include "battle_03.h"

MATCH void func_801E943C(void) {
    BattlePanelStateFuncs3 handlers;

    handlers = D_801D0FB8;
    handlers.handlers[BATTLE_PANEL_TASK->state]();
}

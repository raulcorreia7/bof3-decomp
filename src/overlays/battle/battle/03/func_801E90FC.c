#include "battle_03.h"

MATCH void func_801E90FC(void) {
    BattlePanel0Steps handlers;

    handlers = D_801D0FA0;
    handlers.steps[BATTLE_PANEL_TASK->state]();
}

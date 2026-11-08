#include "game_00.h"

MATCH void func_80199368(void) {
    Game_RunScenarioEntry();
    Menu_DispatchStep();
    Menu_UpdatePanelTasks();
}

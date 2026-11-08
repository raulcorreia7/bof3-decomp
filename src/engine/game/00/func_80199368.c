#include "game_00.h"

MATCH void func_80199368(void) {
    Game_UpdateScenario();
    Menu_DispatchStep();
    Menu_UpdatePanelTasks();
}

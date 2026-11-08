#include "game_00.h"

/* func_80199368 */
MATCH void Game_UpdateMenuFrame(void) {
    Game_UpdateScenario();
    Menu_DispatchStep();
    Menu_UpdatePanelTasks();
}

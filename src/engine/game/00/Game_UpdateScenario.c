#include "game_00.h"

MATCH void Game_UpdateScenario(void) {
    g_ScenarioHandlers[g_ScenarioState.scenario_id]->update();
    Game_UpdateScene();
}

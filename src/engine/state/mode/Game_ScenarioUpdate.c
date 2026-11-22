#include "engine/game/00/game_00.h"

MATCH void Game_ScenarioUpdate(void) {
    g_ScenarioHandlers[g_ScenarioState.scenario_id]->update();
    Game_UpdateScene();
}

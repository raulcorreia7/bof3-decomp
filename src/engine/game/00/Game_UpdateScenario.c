#include "game_00.h"

MATCH void Game_UpdateScenario(void) {
    g_SceneScenes[g_SceneState.scenario_id]->entry();
    Game_UpdateScene();
}

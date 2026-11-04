#include "game_00.h"

MATCH void Game_RunScenarioEntry(void) {
    g_SceneScenes[(s32)g_SceneState.scenario_id]->entry_00();
    Game_RunSceneUpdate();
}

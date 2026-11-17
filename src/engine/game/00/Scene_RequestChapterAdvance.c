#include "game_00.h"

MATCH void Scene_RequestChapterAdvance(void) {
    g_ScenarioState.flags_01 |= SCENARIO_STATE_CHAPTER_ADVANCE;
}

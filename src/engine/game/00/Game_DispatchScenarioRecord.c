#include "game_00.h"

MATCH void Game_DispatchScenarioRecord(void* record) {
    Actor* actor;

    actor = (Actor*)record;
    if (actor->unk_7C & 0x4000) {
        Scene_DispatchObject(actor);
    } else {
        g_SceneScenes[g_SceneState.scenario_id]->entry_04(actor);
    }
    actor->callback_index = GAME_NONE;
}

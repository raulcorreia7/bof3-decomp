#include "engine/game/00/game_00.h"

MATCH void Game_DispatchScenarioRecord(void* record) {
    Actor* actor;

    actor = (Actor*)record;
    if (actor->unk_7C & 0x4000) {
        Scene_DispatchObject(actor);
    } else {
        g_ScenarioHandlers[g_ScenarioState.scenario_id]->record(actor);
    }
    actor->callback_index = GAME_NONE;
}

#include "game_00.h"

MATCH void Scene_LoadOverlay(void) {
    EMI_LoadArchive(g_ScenarioState.scenario_id + EMI_SLOT_SCENA);
}

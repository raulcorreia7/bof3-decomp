#include "engine/game/00/game_00.h"

MATCH void Scene_LoadOverlay(void) {
    EMI_ArchiveLoad(g_ScenarioState.scenario_id + EMI_SLOT_SCENA);
}

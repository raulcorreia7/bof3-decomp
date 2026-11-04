#include "game_00.h"

MATCH void Scene_RequestOverlay(void) {
    EMI_LoaderStreamInitSlot(g_SceneState.scenario_id + EMI_SLOT_SCENA);
}

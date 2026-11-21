#include "area104_14.h"

#include "overlays/area/shared/Area_UpdateTorchGauge.h"

MATCH void func_801F564C(void) {
    AREA_UPDATE_TORCH_GAUGE(!(g_ScenarioState.flags_01 & SCENARIO_STATE_SCRIPT_ACTIVE), (g_Game.members[0].timer == 0), func_801F555C, func_801F5418);
}

#include "area121_14.h"
#include "scenario/state.h"

#include "overlays/area/Area_UpdateTorchGauge.h"

MATCH void func_801F5B90(void) {
    AREA_UPDATE_TORCH_GAUGE(!(g_SceneState.flags_01 & SCENE_STATE_SCRIPT_ACTIVE), (g_Game.members[0].timer == 0), func_801F5AA0, func_801F595C);
}

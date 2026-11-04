#include "game_00.h"

MATCH void Scene_Start(u8 scenario_index) {
    SceneState* state;
    u8*         base;
    s32         index8;
    u16         none_sel;
    u8          ready_phase;

    none_sel           = 0xFFFFu;
    state              = &g_SceneState;
    state->scenario_id = (s8)scenario_index;
    index8             = (s32)((s8)scenario_index) * 8;
    base               = g_SceneFlagWords;
    state->mode_02     = 0u;
    state->unk_03      = 0u;
    state->state_04    = 0u;
    state->timer_06    = 0u;
    state->step_05     = 0u;
    state->flags_01    = 0u;
    state->unk_08      = 0u;

    *(u32*)(base + index8) = 0u;
    g_SceneFlags           = (u32*)(base + ((s32)state->scenario_id * 8));
    ready_phase            = GAME_REQUEST_AREA_CHANGE;
    Scene_RequestOverlay();

    while (!EMI_LoaderIsReady()) {
        if ((g_GameAreaId != none_sel) && (g_GameStateIndex != ready_phase)) {
            func_801992B8();
        }
        CallbackWait(1u);
    }

    Game_RunScenarioEntry();
}

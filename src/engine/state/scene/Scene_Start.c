#include "engine/game/00/game_00.h"

MATCH void Scene_Start(u8 scenario_index) {
    ScenarioState* state;
    u16            none_sel;
    u8             ready_phase;

    none_sel           = 0xFFFFu;
    state              = &g_ScenarioState;
    state->scenario_id = scenario_index;
    state->mode_02     = 0u;
    state->unk_03      = 0u;
    state->state_04    = 0u;
    state->timer_06    = 0u;
    state->step        = 0u;
    state->flags_01    = 0u;
    state->unk_08      = 0u;

    *(u32*)g_SceneFlagRows[(s8)scenario_index] = 0u;
    g_SceneFlags                               = (u32*)g_SceneFlagRows[state->scenario_id];
    ready_phase                                = GAME_REQUEST_AREA_CHANGE;
    Scene_LoadOverlay();

    while (!EMI_IsReady()) {
        if ((g_GameAreaId != none_sel) && (g_GameStateIndex != ready_phase)) {
            Area_RunLoadingFrame();
        }
        SYS_ThreadWait(1u);
    }

    Game_ScenarioUpdate();
}

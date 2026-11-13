#include "area033_13.h"

MATCH void func_801F2D18(void) {
    s32                 i;
    u16                 seed;
    WorldMapMessageRow* rows;
    s8*                 step;
    u8*                 counter;

    step = &g_SceneEventStep;
    switch (*step) {
        case 0:
            Game_SetScriptActive();
            seed = g_GameContextSeed;
            for (i = 0; i < WORLD_MAP_MESSAGE_ROWS; i++) {
                if (seed == D_801F4EA4[i].seed) {
                    break;
                }
            }
            rows = D_801F4EA4;
            Message_StartAreaMessage(rows[i].messages[g_SceneState.scenario_id]);
            g_GameStateIndex = 2;
            counter          = (u8*)&g_SceneEventStep;
            *counter += 1;
            break;

        case 1:
            if (g_GameStateIndex != 2) {
                Game_ClearScriptActive();
                g_SceneEventMode      = 0;
                *step                 = 0;
                g_SceneEventSelection = 0;
            }
            break;
    }
}

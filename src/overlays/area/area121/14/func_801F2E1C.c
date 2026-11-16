#include "area121_14.h"

MATCH void func_801F2E1C(void) {
    s32 i;
    u16 seed;
    s8* step;
    u8* counter;

    step = &g_SceneEventState.step;
    switch (*step) {
        case 0:
            Game_SetScriptActive();
            seed = g_GameContextSeed;
            for (i = 0; i < 4; i++) {
                if (seed == D_801F67BC[i]) {
                    break;
                }
            }
            Message_StartAreaMessage((s16)(i + 1));
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            counter          = (u8*)&g_SceneEventState.step;
            *counter += 1;
            break;

        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode      = 0;
                *step                       = 0;
                g_SceneEventState.selection = 0;
            }
            break;
    }
}

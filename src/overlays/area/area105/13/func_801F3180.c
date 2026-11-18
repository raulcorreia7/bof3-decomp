#include "area105_13.h"

MATCH void func_801F3180(void) {
    s8* state;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_AREA105_TIDE_BLOCKS_PATH);
            *state = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                *state                 = 0;
            }
            return;
    }
}

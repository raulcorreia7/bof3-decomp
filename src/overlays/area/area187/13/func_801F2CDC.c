#include "area187_13.h"

MATCH void func_801F2CDC(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            Message_StartAreaMessage(2);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = (u8)*state + 1;
            break;

        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_ClearEventState();
            }
            break;

        case 2:
            if (g_GameStateIndex != *state) {
                Scene_ClearEventState();
                D_8014504A = 0;
                SYS_ClearFlag(state + 0x63C, 119);
                func_8019FA28(D_80145048, D_80145040, D_80145044, 4);
            }
            break;
    }
}

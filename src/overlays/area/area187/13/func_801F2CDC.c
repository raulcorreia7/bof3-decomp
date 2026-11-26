#include "area187_13.h"
#include "menu/save_data.h"

MATCH void func_801F2CDC(void) {
    s8* state;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            MESSAGE_START_WAIT(MSG_AREA187_ASK_READY_TO_GO);
            *state = (u8)*state + 1;
            break;

        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_ClearEventState();
            }
            break;

        case 2:
            if (g_GameStateIndex != *state) {
                Scene_ClearEventState();
                g_SaveData.return_point.pending = 0;
                SYS_ClearFlag(state + 0x63C, 119);
                func_8019FA28(g_SaveData.return_point.area_id, g_SaveData.return_point.x, g_SaveData.return_point.y, 4);
            }
            break;
    }
}

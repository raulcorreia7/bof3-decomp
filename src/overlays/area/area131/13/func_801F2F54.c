#include "area131_13.h"
#include "menu/save_data.h"

MATCH void func_801F2F54(void) {
    s8* state;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            MESSAGE_START_WAIT(MSG_AREA131_ASK_READY_TO_GO);
            *state = (u8)*state + 1;
            break;

        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_ClearEventState();
            }
            break;

        case 2:
            if (g_GameStateIndex != *state) {
                *state = 3;
            }
            break;

        case 3:
            g_GameFlags ^= 0x16;
            Scene_ClearEventState();
            g_SaveData.return_point.pending = 0;
            SYS_ClearFlag(state + 0x63C, 119);
            func_8019FA28(0x79, 0x1A0000, 0x350000, 3);
            break;
    }
}

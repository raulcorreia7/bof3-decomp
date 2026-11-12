#include "area131_13.h"

MATCH void func_801F2F54(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            Message_StartAreaMessage(2);
            g_GameStateIndex = 2;
            *state           = (u8)*state + 1;
            break;

        case 1:
            if (g_GameStateIndex != 2) {
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
            D_8014504A = 0;
            SYS_ClearFlag(state + 0x63C, 119);
            func_8019FA28(0x79, 0x1A0000, 0x350000, 3);
            break;
    }
}

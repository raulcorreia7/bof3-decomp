#include "game_00.h"

MATCH void func_8019ED40(void) {
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        if (g_Task->unk_0B == 0u) {
            return;
        }
        if (func_8014DAEC() != 0u) {
            g_Task->unk_0B = 1;
        }
        if (g_Task->unk_0B != 2u) {
            return;
        }
    } else if ((func_8014DAEC() != 0u) || (g_Task->unk_0B != 0u)) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}

#include "game_00.h"

MATCH void func_8019ED40(void) {
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        if (g_Task->param.unk_0B == 0u) {
            return;
        }
        if (Actor_StepAnimOnce() != 0u) {
            g_Task->param.unk_0B = 1;
        }
        if (g_Task->param.unk_0B != 2u) {
            return;
        }
    } else if ((Actor_StepAnimOnce() != 0u) || (g_Task->param.unk_0B != 0u)) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}

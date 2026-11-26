#include "game_00.h"

MATCH void func_8019ED40(void) {
    if (g_SysThreads[0].tail.game_entry.request != GAME_REQUEST_IDLE) {
        if (SELF(Actor)->param.unk_0B == 0u) {
            return;
        }
        if (Script_AnimStepOnce() != 0u) {
            SELF(Actor)->param.unk_0B = 1;
        }
        if (SELF(Actor)->param.unk_0B != 2u) {
            return;
        }
    } else if ((Script_AnimStepOnce() != 0u) || (SELF(Actor)->param.unk_0B != 0u)) {
        Actor_Clear();
        return;
    }
    Area_SetDrawMode();
}

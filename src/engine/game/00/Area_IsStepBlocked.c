#include "game_00.h"

MATCH s8 Area_IsStepBlocked(s32 handler_x, s32 handler_y) {
    Actor* saved;
    s8     result;

    GAME_RUN_SCENARIO_ENTRY(entry_08);
    if ((result & BYTE_MASK) == 0) {
        result = func_801A8728(handler_x, handler_y);
    }
    g_SpadWork = saved;
    return result;
}

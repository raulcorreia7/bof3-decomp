#include "game_00.h"

MATCH s8 func_801A79A4(s32 handler_x, s32 handler_y) {
    Actor* saved;
    s8     result;

    GAME_RUN_SCENARIO_ENTRY(entry_0C);
    if ((result & 0xFF) == 0) {
        result = func_801A8B84(handler_x, handler_y);
    }
    g_Task = saved;
    return result;
}

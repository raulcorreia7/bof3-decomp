#include "game_00.h"

MATCH s8 func_801A79A4(s32 handler_x, s32 handler_y) {
    Actor* saved;
    s8     result;

    GAME_RUN_SCENARIO_ENTRY(cell_test);
    if ((result & BYTE_MASK) == 0) {
        result = func_801A8B84(handler_x, handler_y);
    }
    TASK_SET(saved);
    return result;
}

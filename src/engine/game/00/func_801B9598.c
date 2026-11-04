#include "game_00.h"

MATCH s32 func_801B9598(void) {
    s32 result;

    if (g_SpadWork->state_70.byte == 0) {
        result = func_801B95E0();
    } else {
        result = func_801BA678();
    }
    return result & BYTE_MASK;
}

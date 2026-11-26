#include "game_00.h"

MATCH s32 func_801B9598(void) {
    s32 result;

    if (SELF(Actor)->voice_flags.scene_flag == 0) {
        result = func_801B95E0();
    } else {
        result = func_801BA678();
    }
    return result & BYTE_MASK;
}

#include "game_00.h"

MATCH u8 func_801B4494(u8 wanted_code) {
    u8 result;

    if (SELF(Actor)->voice_flags.scene_flag != 0) {
        result = func_801B4D7C(wanted_code);
    } else {
        result = func_801B44DC(wanted_code);
    }
    return result;
}

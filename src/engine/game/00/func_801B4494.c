#include "game_00.h"

MATCH u8 func_801B4494(u8 wanted_code) {
    u8 result;

    if (g_SpadWork->state_70.byte != 0) {
        result = func_801B4D7C(wanted_code);
    } else {
        result = func_801B44DC(wanted_code);
    }
    return result;
}

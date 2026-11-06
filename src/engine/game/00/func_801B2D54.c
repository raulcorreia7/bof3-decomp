#include "game_00.h"

MATCH void func_801B2D54(void) {
    if (func_8014DAEC() & 0xFF) {
        g_GameState->mode_12B.s8_value = 0;
    }
}

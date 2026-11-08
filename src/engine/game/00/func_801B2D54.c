#include "game_00.h"

MATCH void func_801B2D54(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        g_GameState->u.field.mode_12B.s8_value = 0;
    }
}

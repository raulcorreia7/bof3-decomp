#include "game_00.h"

MATCH s32 func_801B5EBC(void) {
    u8 kind;

    kind = g_GameState->slot_index_79;
    if (kind == 2 || kind == 4)
        return 0;
    if (kind == 9 || kind == 10)
        return 0;
    if (!(g_InputPressed & D_80145AC0))
        return 0;
    if (g_GameRequestFlags & 1)
        return 0;
    g_Task->mode = 0x0A;
    ACTOR_CLEAR_STEP();
    g_GameState->mode_12B.u8_value = 8;
    return 1;
}

#include "game_00.h"

MATCH s32 func_801B6044(void) {
    Actor* context;
    Actor* next_context;

    if (g_GameState->leader_id != CHAR_ID_GARR) {
        return 0;
    }
    context = g_Task;
    if ((((u8*)context)[8] & 1) == 0) {
        return 0;
    }
    ((u8*)context)[0xB] = ((u8*)context)[0xB] + 1;
    next_context        = g_Task;
    if (((u8*)next_context)[0xB] != 0x10) {
        return 0;
    }
    ((u8*)next_context)[1]         = 0xA;
    TASK_BYTES[2]                  = 0;
    g_GameState->mode_12B.u8_value = 8;
    return 1;
}

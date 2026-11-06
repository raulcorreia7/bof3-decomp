#include "game_00.h"

MATCH bool func_801B544C(void) {
    bool found = false;
    s32  i;
    u8   index;

    index = g_GameState->slot_13C;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        return false;
    }
    if (g_GameRequestFlags & 1) {
        return false;
    }
    g_GameState->step_12A.u8_value++;
    if (g_GameState->step_12A.u8_value < 0xF1U) {
        return false;
    }
    g_GameState->step_12A.u8_value = 0;
    for (i = 1; i < g_PartySize; i++) {
        if (D_80145FBB[i].mode == 9) {
            found = true;
        }
    }
    if (!(found & BYTE_MASK)) {
        if (rand() & 1) {
            g_GameState->mode_12B.u8_value = 9;
            Actor_RequestScript(g_Task->direction_08);
            TASK_BYTES[0x9] = 2;
            TASK_BYTES[0x1] = 6;
            ACTOR_CLEAR_STEP();
            return true;
        }
    }
    return false;
}

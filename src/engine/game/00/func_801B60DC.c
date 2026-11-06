#include "game_00.h"

MATCH void func_801B60DC(s32 actor_index) {
    s32 index;

    index = actor_index & 0xFF;
    if (D_8014688E[index * ACTOR_SIZE] != 9) {
        g_Actors[index].interaction_flags |= ACTOR_FLAG_SCRIPT_PENDING;
        func_801B5BDC(g_Task->direction_08);
        ACTOR_CLEAR_STEP();
        g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
        return;
    }
    /* NOTE: a non-volatile first read keeps the 1 in the delay slot. */
    if ((*(u8*)&g_GameRequestFlags & 0x21) != 1) {
        if (!(g_GameRequestFlags & 0x20)) {
            if (s_RouteSlotAlternates[g_GameState->slot_index_79] != 0) {
                Actor_RequestScript((g_Task->direction_08 >> 1) + 0x34);
            } else {
                Actor_RequestScript(g_Task->direction_08);
            }
        }
        g_GameState->slot_12D = actor_index;
        g_Task->header.mode   = 0xB;
        ACTOR_CLEAR_STEP();
    }
}

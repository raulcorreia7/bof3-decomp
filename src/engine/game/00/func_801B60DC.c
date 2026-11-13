#include "game_00.h"

MATCH void func_801B60DC(s32 actor_index) {
    s32 index;

    index = actor_index & BYTE_MASK;
    if (D_8014688E[index * ACTOR_SIZE] != 9) {
        g_Actors[index].interaction_flags |= ACTOR_FLAG_SCRIPT_PENDING;
        func_801B5BDC(g_Task->direction_08);
        ACTOR_CLEAR_STEP();
        g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
        return;
    }
    /* NOTE: a non-volatile first read keeps the 1 in the delay slot. */
    if ((*(u8*)&g_GameRequestFlags & (AREA_LOAD_FLAG_NO_ACTOR_SCRIPT | AREA_LOAD_FLAG_WORLD_MAP)) != 1) {
        if (!(g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            if (s_RouteSlotAlternates[g_Game.current->chr.character_id] != 0) {
                Actor_RequestScript((g_Task->direction_08 >> 1) + 0x34);
            } else {
                Actor_RequestScript(g_Task->direction_08);
            }
        }
        g_Game.current->status.field.slot_12D = actor_index;
        g_Task->header.mode                   = 0xB;
        ACTOR_CLEAR_STEP();
    }
}

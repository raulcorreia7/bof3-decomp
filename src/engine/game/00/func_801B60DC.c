#include "game_00.h"

MATCH void func_801B60DC(s32 actor_index) {
    s32 index;

    index = actor_index & BYTE_MASK;
    if (D_8014688E[index * ACTOR_SIZE] != 9) {
        g_Actors[index].interaction_flags |= ACTOR_INTERACTION_SCRIPT_PENDING;
        Actor_RequestRoute(g_Task->direction);
        ACTOR_CLEAR_STEP();
        g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
        return;
    }
    if ((*(u8*)&g_GameRequestFlags & (AREA_LOAD_FLAG_NO_ACTOR_SCRIPT | AREA_LOAD_FLAG_WORLD_MAP)) != 1) {
        if (!(g_GameRequestFlags & AREA_LOAD_FLAG_NO_ACTOR_SCRIPT)) {
            if (s_RouteSlotAlternates[g_Game.current->chr.character_id] != 0) {
                Actor_RequestScript((g_Task->direction >> 1) + 0x34);
            } else {
                Actor_RequestScript(g_Task->direction);
            }
        }
        g_Game.current->status.field.slot = actor_index;
        g_Task->header.mode               = 0xB;
        ACTOR_CLEAR_STEP();
    }
}

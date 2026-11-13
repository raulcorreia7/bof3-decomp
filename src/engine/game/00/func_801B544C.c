#include "game_00.h"

MATCH bool func_801B544C(void) {
    bool found = false;
    s32  i;
    u8   index;

    index = g_Game.current->character_index;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        return false;
    }
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
        return false;
    }
    g_Game.current->u.field.step_12A.u8_value++;
    if (g_Game.current->u.field.step_12A.u8_value < 0xF1U) {
        return false;
    }
    g_Game.current->u.field.step_12A.u8_value = 0;
    for (i = 1; i < g_Game.party_size; i++) {
        if (g_Game.members[i].u.field.mode_12B.u8_value == 9) {
            found = true;
        }
    }
    if (!(found & BYTE_MASK)) {
        if RANDOM_MASK (1) {
            g_Game.current->u.field.mode_12B.u8_value = 9;
            Actor_RequestScript(g_Task->direction_08);
            g_Task->timer       = 2;
            g_Task->header.mode = 6;
            ACTOR_CLEAR_STEP();
            return true;
        }
    }
    return false;
}

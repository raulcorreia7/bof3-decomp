#include "game_00.h"

MATCH bool func_801BD938(void) {
    u8 index;
    u8 slot;

    if (g_Game.members[0].u.field.mode.unsigned_value == 8) {
        return 0;
    }
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        return 0;
    }
    index = g_Game.current->character_index;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        return 0;
    }
    g_Game.current->u.field.step.unsigned_value++;
    if (g_Game.current->u.field.step.unsigned_value < 0xF1U) {
        return 0;
    }
    g_Game.current->u.field.step.unsigned_value = 0;
    if (g_Game.members[0].u.field.mode.unsigned_value == 9) {
        return 0;
    }
    slot = SELF(Actor)->unk_05;
    if (g_Game.members[slot ^ 0x3].u.field.mode.unsigned_value == 9) {
        return 0;
    }
    if (slot == (RANDOM_MASK(1) + 1)) {
        g_Game.current->u.field.mode.unsigned_value = 9;
        Script_Request(SELF(Actor)->direction);
        SELF(Actor)->timer       = 2;
        SELF(Actor)->header.mode = 6;
        ACTOR_CLEAR_STEP();
        return 1;
    }
    return 0;
}

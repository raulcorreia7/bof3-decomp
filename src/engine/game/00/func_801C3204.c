#include "game_00.h"

MATCH void func_801C3204(void) {
    u8 index;

    index = g_GameState->character_index;
    if (g_Characters[index].status & STATUS_POISONED) {
        g_GameState->u.field.flags_118 = 0x0A;
    }
    index = g_GameState->character_index;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        g_GameState->u.field.countdown_119 = 0x28;
    }
}

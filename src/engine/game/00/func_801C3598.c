#include "game_00.h"

MATCH void func_801C3598(void) {
    u8 index;

    index = g_GameState->character_index;
    if (g_Characters[index].status & STATUS_CONFUSED) {
        g_GameState->u.field.countdown_119--;
        if (g_GameState->u.field.countdown_119 == 0) {
            index = g_GameState->character_index;
            g_Characters[index].status &= ~STATUS_CONFUSED;
        }
    }
}

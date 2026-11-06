#include "game_00.h"

MATCH void func_801C3598(void) {
    u8 index;

    index = g_GameState->slot_13C;
    if (g_SaveData.characters[index].status & STATUS_CONFUSED) {
        g_GameState->countdown_119--;
        if (g_GameState->countdown_119 == 0) {
            index = g_GameState->slot_13C;
            g_SaveData.characters[index].status &= ~STATUS_CONFUSED;
        }
    }
}

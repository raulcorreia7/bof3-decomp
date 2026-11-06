#include "game_00.h"

MATCH void func_801C3204(void) {
    u8 index;

    index = g_GameState->slot_13C;
    if (g_SaveData.characters[index].status & STATUS_POISONED) {
        g_GameState->flags_118 = 0x0A;
    }
    index = g_GameState->slot_13C;
    if (g_SaveData.characters[index].status & STATUS_CONFUSED) {
        g_GameState->countdown_119 = 0x28;
    }
}

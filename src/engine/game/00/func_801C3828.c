#include "game_00.h"

MATCH void func_801C3828(void) {
    if (func_801C38F4(g_GameState->character_index, 3, 0x16) & BYTE_MASK) {
        Char_AddHP(1, g_GameState->chr.character_id);
    }
    if (func_801C38F4(g_GameState->character_index, 3, 0x17) & BYTE_MASK) {
        Char_AddHP(1, g_GameState->chr.character_id);
    }
    if (func_801C38F4(g_GameState->character_index, 2, 0x1F) & BYTE_MASK) {
        Char_AddHP(1, g_GameState->chr.character_id);
    }
}

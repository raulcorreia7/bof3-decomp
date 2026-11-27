#include "game_00.h"

MATCH void func_801B3690(void) {
    u8 hint;

    hint = g_EmiLoadedCharacterIndex;
    g_PersonalActions[hint & 0x7F]();
    if (g_Game.current->u.field.mode.unsigned_value == 0) {
        Script_Request(SELF(Actor)->direction);
        Party_BattlersClearState(CHAR_INDEX_RYU);
        SELF(Actor)->header.mode = 1;
    }
}

#include "game_00.h"

MATCH void func_801B3690(void) {
    u8 hint;

    hint = g_EmiLoadedCharacterIndex;
    g_PersonalActions[hint & 0x7F]();
    if (g_Game.current->u.field.mode_12B.u8_value == 0) {
        Actor_RequestScript(g_Task->direction_08);
        Party_ClearBattlerState(CHAR_INDEX_RYU);
        g_Task->header.mode = 1;
    }
}

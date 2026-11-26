#include "game_00.h"

MATCH void func_801B2C38(void) {
    if (g_Game.input != 0) {
        g_Game.current->u.field.mode.unsigned_value = 0U;
    } else {
        D_801CD1D8[g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK]();
    }
    if (g_Game.current->u.field.mode.unsigned_value == 0) {
        Script_Request(SELF(Actor)->direction);
        SELF(Actor)->timer = 0;
        Party_BattlersClearState(CHAR_INDEX_RYU);
        SELF(Actor)->header.mode  = 1;
        SELF(Actor)->param.unk_0B = 0;
        func_801B036C();
    }
}

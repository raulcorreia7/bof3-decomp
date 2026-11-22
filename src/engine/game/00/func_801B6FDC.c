#include "game_00.h"

MATCH void func_801B6FDC(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    g_Game.current->u.field.flags &= 0xDFu;
    TASK(Actor)->unk_03 = 0;
}

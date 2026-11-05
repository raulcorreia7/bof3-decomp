#include "game_00.h"

MATCH void func_801AD9C4(void) {
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }

    g_Task->unk_04 = 5;
}

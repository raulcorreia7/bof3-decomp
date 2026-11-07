#include "area175_13.h"

MATCH void func_801F3324(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        g_Task->timer       = 0x10;
        g_Task->header.mode = 3;
    }
    func_801F3438();
}

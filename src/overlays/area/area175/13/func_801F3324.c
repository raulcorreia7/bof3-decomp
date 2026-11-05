#include "area175_13.h"

MATCH void func_801F3324(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        g_Task->unk_09 = 0x10;
        g_Task->mode   = 3;
    }
    func_801F3438();
}

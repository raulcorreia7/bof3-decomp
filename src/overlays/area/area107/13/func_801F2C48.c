#include "area107_13.h"

MATCH void func_801F2C48(void) {
    void* state;

    if (g_GameStateIndex == GAME_REQUEST_BATTLE) {
        state                  = g_Task;
        FIELD(u8, state, 0x1u) = 1;
    }
}

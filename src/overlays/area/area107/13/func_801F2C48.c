#include "area107_13.h"

MATCH void func_801F2C48(void) {
    Actor* state;

    if (g_GameStateIndex == GAME_REQUEST_BATTLE) {
        state              = SELF(Actor);
        state->header.mode = 1;
    }
}

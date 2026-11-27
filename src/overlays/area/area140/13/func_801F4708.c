#include "area140_13.h"

MATCH void func_801F4708(void) {
    u8* work;

    work = SELF(u8);
    work[9]--;
    if (work[9] == 0) {
        SELF(Actor)->header.mode = 2;
    }
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        SELF(Actor)->header.mode = 2;
    }
}

#include "area175_13.h"

MATCH void func_801F3324(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        SELF(Actor)->timer       = 16;
        SELF(Actor)->header.mode = 3;
    }
    Area_DrawScreenTint();
}

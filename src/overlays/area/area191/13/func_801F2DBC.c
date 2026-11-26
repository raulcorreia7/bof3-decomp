#include "area191_13.h"

MATCH void func_801F2DBC(void) {
    u8* state;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        state                    = &g_ScenarioState.step;
        *state                   = *state + 1;
        SELF(Actor)->header.mode = 3;
    }
    Area_DrawScreenTint();
}

#include "area134_13.h"

MATCH void func_801F3C98(void) {
    u8 step;

    step                     = SELF(Actor)->header.step;
    SELF(Actor)->header.step = step + 1;
    if (step >= 0xF) {
        SELF(Actor)->header.mode = 0xD;
    } else {
        if (g_ScriptVars[1] == GAME_NONE || g_ScriptVars[2] == 0x80) {
            /* FAKE: pin the scratchpad base to v0 for the mode store. */
            FAKE_REG(Actor*, work, "v0");
            work              = SELF(Actor);
            work->header.mode = 0x17;
        } else {
            g_ScriptVars[1] = 0;
            ACTOR_SET_MODE(0);
        }
        SELF(Actor)->header.step = 0;
    }
}

#include "area134_13.h"

/* FAKE: pin the scratchpad base to v0 for the mode branch. */
MATCH void func_801F33C0(void) {
    FAKE_REG(Actor*, work, "v0");

    if (g_ScriptVars[1] == GAME_NONE || g_ScriptVars[2] == 0x80) {
        work              = g_Task;
        work->header.mode = 0x17;
    } else {
        g_ScriptVars[1] = 0;
        ACTOR_SET_MODE(0);
    }
    g_Task->header.step = 0;
}

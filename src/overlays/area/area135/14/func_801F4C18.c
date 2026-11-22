#include "area135_14.h"

MATCH void func_801F4C18(void) {
    Actor* work;

    TASK(Actor)->direction = FACING_LEFT;
    g_ScriptState->steps   = ((s32)(TASK(Actor)->pos.x.fixed + 0xFFE38000) >> 0xF);
    if ((s8)g_ScriptState->steps < 0) {
        TASK(Actor)->direction ^= 4;
        g_ScriptState->steps = -g_ScriptState->steps;
    }
    Area_MoveActorRoute(g_ScriptState, TASK(Actor)->direction);
    work = TASK(Actor);
    work->unk_04 += 1;
    work->vz = 0;
    g_ScriptState->cursor -= 2;
}

#include "area144_13.h"

MATCH void func_801F3B24(void) {
    s32 diff;

    diff = (TO_COORD(28) - SELF(Actor)->pos.y.fixed) >> 15;
    if (diff != 0) {
        SELF(Actor)->direction = FACING_UP;
        g_ScriptState->steps   = abs(diff);
        Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
    }
    g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
}

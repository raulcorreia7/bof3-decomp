#include "area144_13.h"

MATCH void func_801F3B24(void) {
    s32 diff;

    diff = (TO_COORD(28) - g_Task->pos.y.fixed) >> 15;
    if (diff != 0) {
        g_Task->direction_08  = FACING_UP;
        g_ScriptState->unk_07 = abs(diff);
        Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
    }
    g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
}

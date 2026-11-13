#include "area135_14.h"

MATCH void func_801F4C18(void) {
    Actor* work;

    g_Task->direction_08  = FACING_LEFT;
    g_ScriptState->unk_07 = ((s32)(g_Task->pos.x.fixed + 0xFFE38000) >> 0xF);
    if ((s8)g_ScriptState->unk_07 < 0) {
        g_Task->direction_08 ^= 4;
        g_ScriptState->unk_07 = -g_ScriptState->unk_07;
    }
    Area_MoveActorRoute(g_ScriptState, g_Task->direction_08);
    work = g_Task;
    work->unk_04 += 1;
    work->vz = 0;
    g_ScriptState->cursor -= 2;
}

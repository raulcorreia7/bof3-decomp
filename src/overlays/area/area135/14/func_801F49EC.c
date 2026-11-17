#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F49EC(void) {
    Actor* work;
    u8     count;
    s32    delta;
    s32    y_offset;

    count    = func_801F5D1C();
    y_offset = -TO_COORD_HALF(12);
    /* FAKE: retail forms the fixed-point offset before the task read. */
    FAKE_BARRIER();
    g_Task->direction     = FACING_DOWN;
    delta                 = g_Task->pos.y.fixed + y_offset;
    g_ScriptState->unk_07 = ((s32)((count << 17) - delta) >> 0xF);
    if ((s8)g_ScriptState->unk_07 < 0) {
        g_ScriptState->unk_07 = -g_ScriptState->unk_07;
        g_Task->direction ^= 4;
    }
    if (g_ScriptState->unk_07 != 0) {
        Area_MoveActorRoute(g_ScriptState, g_Task->direction);
        g_Task->vz = 0;
    }
    work = g_Task;
    work->unk_04 += 1;
    g_ScriptState->cursor -= 2;
}
#else
INCLUDE_ASM(func_801F49EC);
#endif

#include "area135_14.h"

/* Steps the actor up or down toward the row from func_801F5D1C and repeats the script step until it arrives. */
MATCH void func_801F49EC(void) {
    Actor* work;
    u8     count;
    s32    delta;
    u32    magnitude;
    s32    y_offset;

    count    = func_801F5D1C();
    y_offset = -TO_COORD_HALF(12);
    /* FAKE: retail forms the fixed-point offset before the task read. */
    FAKE_BARRIER();
    SELF(Actor)->direction = FACING_DOWN;
    delta                  = SELF(Actor)->pos.y.fixed + y_offset;
    g_ScriptState->steps   = ((s32)((count << 17) - delta) >> 0xF);
    if ((s8)g_ScriptState->steps < 0) {
        magnitude            = (u8)g_ScriptState->steps;
        g_ScriptState->steps = -magnitude;
        SELF(Actor)->direction ^= 4;
    }
    if (g_ScriptState->steps != 0) {
        Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
        SELF(Actor)->vz = 0;
    }
    work = SELF(Actor);
    work->unk_04 += 1;
    g_ScriptState->cursor -= 2;
}

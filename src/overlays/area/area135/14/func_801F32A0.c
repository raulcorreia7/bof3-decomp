#include "area135_14.h"

MATCH void func_801F32A0(s32 value) {
    Actor* work;
    s32    x;
    /* FAKE: pin the focus z copy to a2. */
    FAKE_REG(s32, z, "a2");

    work              = TASK(Actor);
    work->pos.x.fixed = g_PartyActors[0].pos.x.fixed;
    FAKE_BARRIER(); /* FAKE: keeps the focus y load after the x store. */
    work->pos.y.fixed = g_AreaFocusY;
    x                 = work->pos.x.fixed;
    FAKE_BARRIER(); /* FAKE: keeps the focus z load after the y store. */
    z                         = g_PartyActors[0].pos.z.fixed;
    work->pos.z.fixed         = z;
    g_AreaHeightOffsetEnabled = 1;
    TASK(Actor)->vz           = Area_HeightRead(x, work->pos.y.fixed) << 16;
}

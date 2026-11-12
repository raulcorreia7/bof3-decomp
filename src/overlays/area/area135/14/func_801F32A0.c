#include "area135_14.h"

MATCH void func_801F32A0(s32 value) {
    Actor* work;
    s32    x;
    /* FAKE: pin the focus z copy to a2. */
    FAKE_REG(s32, z, "a2");

    work              = g_Task;
    work->pos.x.fixed = D_80147A8C;
    FAKE_BARRIER(); /* FAKE: keeps the focus y load after the x store. */
    work->pos.y.fixed = g_AreaFocusY;
    x                 = work->pos.x.fixed;
    FAKE_BARRIER(); /* FAKE: keeps the focus z load after the y store. */
    z                         = D_80147A94;
    work->pos.z.fixed         = z;
    g_AreaHeightOffsetEnabled = 1;
    g_Task->vz                = Area_ReadHeight(x, work->pos.y.fixed) << 16;
}

#include "area189_13.h"

MATCH void func_801F559C(void) {
    Actor* work;

    work = g_Task;
    work->pos.x.fixed += work->vx;
    g_AreaScrollTargetX = work->pos.x.fixed;
    FAKE_BARRIER(); /* FAKE: the y block starts after the x target store. */
    work->pos.y.fixed += work->vy;
    g_AreaScrollTargetY = work->pos.y.fixed;
    FAKE_BARRIER(); /* FAKE: the refresh request follows the y target store. */
    g_AreaCameraRefreshCount = 2;
    work->pos.z.fixed += work->vz;
}

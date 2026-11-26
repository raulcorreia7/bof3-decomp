#include "area189_13.h"

MATCH void func_801F559C(void) {
    Actor* work;

    work = SELF(Actor);
    work->pos.x.fixed += work->vx;
    g_AreaScrollTargetCoordX.fixed = work->pos.x.fixed;
    work->pos.y.fixed += work->vy;
    g_AreaScrollTargetCoordY.fixed = work->pos.y.fixed;
    g_AreaCameraRefreshCount       = 2;
    work->pos.z.fixed += work->vz;
}

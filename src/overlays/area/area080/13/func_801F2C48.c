#include "area080_13.h"

MATCH void func_801F2C48(void) {
    Actor*    work;
    AreaRing* ring;

    work = g_Task;
    WorldPos_Copy(&work->pos, &D_80146954);

    ring            = (AreaRing*)AREA_WORK;
    D_801F44A0      = ring;
    ring->base[0]   = work->pos.x.fixed;
    ring->base[1]   = work->pos.y.fixed;
    ring->base[2]   = work->pos.z.fixed + TO_COORD(2048);
    ring->center[0] = work->pos.x.fixed;
    ring->center[1] = work->pos.y.fixed;
    ring->center[2] = work->pos.z.fixed;
    ring->unk_22    = 32;
    ring->unk_23    = 0;
    ring->radius    = 0;

    func_801F3834();

    g_Task->timer = AREA_RING_STEP_FRAMES;
    g_Task->header.mode += 1;
}

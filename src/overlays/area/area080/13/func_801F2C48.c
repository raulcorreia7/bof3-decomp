#include "area080_13.h"

MATCH void func_801F2C48(void) {
    Actor*    work;
    AreaRing* ring;

    work = SELF(Actor);
    WorldPos_Copy(&work->pos, &D_80146954);

    ring       = (AreaRing*)AREA_WORK;
    D_801F44A0 = ring;
    setVector(&ring->base, work->pos.x.fixed, work->pos.y.fixed, work->pos.z.fixed + TO_COORD(2048));
    setVector(&ring->center, work->pos.x.fixed, work->pos.y.fixed, work->pos.z.fixed);
    ring->unk_22 = 32;
    ring->unk_23 = 0;
    ring->radius = 0;

    func_801F3834();

    SELF(Actor)->timer = AREA_RING_STEP_FRAMES;
    SELF(Actor)->header.mode += 1;
}

#include "area102_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    work                          = TASK(Actor);
    work->unk_0A                  = D_801F3944[(COORD_INT(work->pos.x) & 0x1) | ((COORD_INT(work->pos.y) & 0x1) << 1)];
    TASK(Actor)->timer            = TASK(Actor)->unk_0A + (RANDOM_MASK(0x2F));
    Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), 0);
    TASK(Actor)->header.step++;
}

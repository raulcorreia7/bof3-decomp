#include "area102_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;

    COORD_INT(SELF(Actor)->pos.z) = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    work                          = SELF(Actor);
    work->unk_0A                  = D_801F3944[(COORD_INT(work->pos.x) & 0x1) | ((COORD_INT(work->pos.y) & 0x1) << 1)];
    SELF(Actor)->timer            = SELF(Actor)->unk_0A + (RANDOM_MASK(0x2F));
    Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), 0);
    SELF(Actor)->header.step++;
}

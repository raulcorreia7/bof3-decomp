#include "area102_13.h"

MATCH void func_801F2E28(void) {
    func_801F2F44(7);
    SELF(Actor)->timer += 1;
    if ((u8)SELF(Actor)->timer >= 31U) {
        Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), 0);
        SELF(Actor)->timer = 31;
        SELF(Actor)->header.step += 1;
    }
}

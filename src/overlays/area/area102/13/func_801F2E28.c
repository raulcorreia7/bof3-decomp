#include "area102_13.h"

MATCH void func_801F2E28(void) {
    func_801F2F44(7);
    TASK(Actor)->timer += 1;
    if ((u8)TASK(Actor)->timer >= 31U) {
        Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), 0);
        TASK(Actor)->timer = 31;
        TASK(Actor)->header.step += 1;
    }
}

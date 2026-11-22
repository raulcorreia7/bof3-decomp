#include "area102_13.h"

MATCH void func_801F2D84(void) {
    func_801F2F44(TASK(Actor)->timer);
    TASK(Actor)->timer += 1;
    if ((u8)TASK(Actor)->timer >= 8U) {
        Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), 0x8A);
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
}

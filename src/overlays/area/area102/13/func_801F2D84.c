#include "area102_13.h"

MATCH void func_801F2D84(void) {
    func_801F2F44(SELF(Actor)->timer);
    SELF(Actor)->timer += 1;
    if ((u8)SELF(Actor)->timer >= 8U) {
        Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), 0x8A);
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step += 1;
    }
}

#include "area048_13.h"

MATCH void func_801F4148(void) {
    func_801F41F0(COORD_INT(SELF(Actor)->pos.x), D_801F4E74[SELF(Actor)->timer >> 1]);
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer >= 7) {
        SELF(Actor)->timer       = 0;
        SELF(Actor)->header.step = 3;
    }
    func_801F4258(COORD_INT(SELF(Actor)->pos.x));
}

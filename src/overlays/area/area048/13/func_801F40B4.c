#include "area048_13.h"

MATCH void func_801F40B4(void) {
    func_801F41F0(COORD_INT(SELF(Actor)->pos.x), D_801F4E70[(u8)(SELF(Actor)->timer / 3)]);
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer >= 4) {
        SELF(Actor)->header.step = 1;
    }
}

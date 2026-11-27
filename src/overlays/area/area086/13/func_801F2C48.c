#include "area086_13.h"

MATCH void func_801F2C48(void) {
    COORD_FRAC(SELF(Actor)->pos.x) = D_801F3664[COORD_INT(SELF(Actor)->pos.x)];
    COORD_INT(SELF(Actor)->pos.z)  = D_801F3668[COORD_INT(SELF(Actor)->pos.y)];
    SELF(Actor)->header.step++;
    func_801F2DE8();
    func_801F3070();
}

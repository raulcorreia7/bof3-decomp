#include "area086_13.h"

MATCH void func_801F2C48(void) {
    COORD_FRAC(TASK(Actor)->pos.x) = D_801F3664[COORD_INT(TASK(Actor)->pos.x)];
    COORD_INT(TASK(Actor)->pos.z)  = D_801F3668[COORD_INT(TASK(Actor)->pos.y)];
    TASK(Actor)->header.step++;
    func_801F2DE8();
    func_801F3070();
}

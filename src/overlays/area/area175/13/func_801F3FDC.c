#include "area175_13.h"

MATCH void func_801F3FDC(void) {
    if (g_AreaScrollTargetX <= TO_COORD(46)) {
        SELF(Actor)->pos.x.fixed = g_AreaScrollTargetX;
    }
}

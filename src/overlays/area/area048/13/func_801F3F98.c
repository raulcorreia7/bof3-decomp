#include "area048_13.h"

MATCH void func_801F3F98(void) {
    if (((COORD_INT(TASK(Actor)->pos.x) == 0) && (SYS_TestFlag(g_SceneEventFlags, 13) == 0)) || ((COORD_INT(TASK(Actor)->pos.x) != 0) && (D_8014686B == 0))) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 65U) {
        TASK(Actor)->timer = 0;
        if (RANDOM_MASK(1)) {
            TASK(Actor)->header.step = 5;
        }
    }
    func_801F4258(COORD_INT(TASK(Actor)->pos.x));
}

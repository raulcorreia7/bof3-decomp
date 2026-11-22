#include "area086_13.h"

MATCH void func_801F2D28(void) {
    COORD_INT(TASK(Actor)->pos.z) += D_801F3670[COORD_INT(TASK(Actor)->pos.y)];
    TASK(Actor)->timer++;
    if (TASK(Actor)->timer >= 16) {
        COORD_INT(TASK(Actor)->pos.y) = (COORD_INT(TASK(Actor)->pos.y) + 1) & 3;
        /* FAKE: retail reads SYS_ClearFlag as void(void*, u16). */
        ((void (*)(void*, u16))SYS_ClearFlag)(g_SceneEventFlags, COORD_FRAC(TASK(Actor)->pos.x));
        TASK(Actor)->header.step--;
    }
    func_801F2DE8();
    func_801F3070();
}

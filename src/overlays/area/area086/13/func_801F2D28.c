#include "area086_13.h"

MATCH void func_801F2D28(void) {
    COORD_INT(SELF(Actor)->pos.z) += D_801F3670[COORD_INT(SELF(Actor)->pos.y)];
    SELF(Actor)->timer++;
    if (SELF(Actor)->timer >= 16) {
        COORD_INT(SELF(Actor)->pos.y) = (COORD_INT(SELF(Actor)->pos.y) + 1) & 3;
        /* FAKE: retail reads SYS_ClearFlag as void(void*, u16). */
        ((void (*)(void*, u16))SYS_ClearFlag)(g_SceneEventFlags, COORD_FRAC(SELF(Actor)->pos.x));
        SELF(Actor)->header.step--;
    }
    func_801F2DE8();
    func_801F3070();
}

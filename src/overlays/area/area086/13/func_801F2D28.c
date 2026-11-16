#include "area086_13.h"
#include "area/spad.h"

MATCH void func_801F2D28(void) {
    COORD_INT(g_Task->pos.z) += D_801F3670[COORD_INT(g_Task->pos.y)];
    g_Task->timer++;
    if (g_Task->timer >= 16) {
        COORD_INT(g_Task->pos.y) = (COORD_INT(g_Task->pos.y) + 1) & 3;
        /* FAKE: retail reads SYS_ClearFlag as void(void*, u16). */
        ((void (*)(void*, u16))SYS_ClearFlag)(g_SceneEventFlags, COORD_FRAC(g_Task->pos.x));
        g_Task->header.step--;
    }
    func_801F2DE8();
    func_801F3070();
}

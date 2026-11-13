#include "area140_13.h"

MATCH void func_801F3320(void) {
    s32 i;

    i                        = COORD_INT(g_Task->pos.x);
    COORD_INT(g_Task->pos.x) = D_801F47F4[i].x;
    COORD_INT(g_Task->pos.y) = D_801F47F4[i].y;
    g_Task->direction_08     = D_801F47F4[i].direction;
    g_Task->param.unk_0B     = D_801F47F4[i].param;
    if (g_Task->direction_08 == FACING_UP_LEFT) {
        COORD_INT(g_Task->pos.z) = 0;
        g_Task->header.step++;
    } else {
        COORD_INT(g_Task->pos.z) = 128;
        g_Task->header.step      = 4;
    }
    func_801F3950(g_Task->direction_08, COORD_INT(g_Task->pos.z));
}

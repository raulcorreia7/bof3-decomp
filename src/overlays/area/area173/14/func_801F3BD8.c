#include "area173_14.h"

MATCH void func_801F3BD8(void) {
    s32 index;

    index                    = COORD_INT(g_Task->pos.x);
    g_Task->param.unk_0B     = index;
    COORD_INT(g_Task->pos.x) = D_801F5304[index].x;
    COORD_INT(g_Task->pos.y) = D_801F5304[index].y;
    g_Task->direction_08     = D_801F5308[index];
    SYS_SetFlag(g_SceneEventFlags, g_Task->direction_08);
    g_Task->screen_y = 0;
    g_Task->header.step++;
    func_801F3FBC(0, 1);
    func_801F3FBC(1, 1);
}

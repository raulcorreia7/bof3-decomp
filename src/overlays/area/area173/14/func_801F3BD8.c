#include "area173_14.h"

MATCH void func_801F3BD8(void) {
    s32 index;

    index                         = COORD_INT(TASK(Actor)->pos.x);
    TASK(Actor)->param.unk_0B     = index;
    COORD_INT(TASK(Actor)->pos.x) = D_801F5304[index].x;
    COORD_INT(TASK(Actor)->pos.y) = D_801F5304[index].y;
    TASK(Actor)->direction        = D_801F5308[index];
    SYS_SetFlag(g_SceneEventFlags, TASK(Actor)->direction);
    TASK(Actor)->screen_y = 0;
    TASK(Actor)->header.step++;
    func_801F3FBC(0, 1);
    func_801F3FBC(1, 1);
}

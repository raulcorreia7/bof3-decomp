#include "area173_14.h"

MATCH void func_801F3BD8(void) {
    s32 index;

    index                         = COORD_INT(SELF(Actor)->pos.x);
    SELF(Actor)->param.unk_0B     = index;
    COORD_INT(SELF(Actor)->pos.x) = D_801F5304[index].x;
    COORD_INT(SELF(Actor)->pos.y) = D_801F5304[index].y;
    SELF(Actor)->direction        = D_801F5308[index];
    SYS_SetFlag(g_SceneEventFlags, SELF(Actor)->direction);
    SELF(Actor)->screen_y = 0;
    SELF(Actor)->header.step++;
    func_801F3FBC(0, 1);
    func_801F3FBC(1, 1);
}

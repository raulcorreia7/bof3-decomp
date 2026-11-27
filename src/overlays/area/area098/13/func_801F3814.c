#include "area098_13.h"

MATCH void func_801F3814(void) {
    Actor*    work;
    WorldPos* pos;
    s32       z;

    work           = SELF(Actor);
    pos            = &g_Game.members[0].pos;
    work->angle_x  = pos->x.fixed;
    work->angle_y  = pos->y.fixed;
    z              = pos->z.fixed + 0x800000;
    work->timer    = 8;
    work->screen_x = 0;
    work->angle_z  = z;
    SELF(Actor)->header.mode++;
}

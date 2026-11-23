#include "area188_13.h"

MATCH void func_801F3304(void) {
    Actor*    work;
    WorldPos* pos;
    s32       z;

    work           = TASK(Actor);
    pos            = &g_Game.members[0].pos;
    work->angle_x  = pos->x.fixed;
    work->angle_y  = pos->y.fixed;
    z              = pos->z.fixed + 0x800000;
    work->timer    = 8;
    work->screen_x = 0;
    work->angle_z  = z;
    TASK(Actor)->header.mode++;
}

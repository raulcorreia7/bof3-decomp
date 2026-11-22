#include "area188_13.h"

MATCH void func_801F3304(void) {
    Actor*    work;
    WorldPos* pos;
    s32       z;

    work           = TASK(Actor);
    pos            = &g_Game.members[0].pos;
    work->unk_64   = pos->x.fixed;
    work->unk_68   = pos->y.fixed;
    z              = pos->z.fixed + 0x800000;
    work->timer    = 8;
    work->screen_x = 0;
    work->unk_6C   = z;
    TASK(Actor)->header.mode++;
}

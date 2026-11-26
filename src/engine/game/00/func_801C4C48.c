#include "game_00.h"

MATCH void func_801C4C48(void) {
    Actor* work;
    u8     step;
    s32    x;
    s32    y;

    work = SELF(Actor);
    step = work->timer;
    x    = work->pos.x.fixed + (work->vx * step);
    y    = work->pos.y.fixed + (work->vy * step);
    Area_HeightReadStep(x, y, work->direction);
    if ((SP_REF(u8, 0x0u) == 0) && ((Area_HeightRead(x, y) - COORD_INT(SELF(Actor)->pos.z)) >= 0x80)) {
        g_Game.current->u.field.counter.unsigned_value = (u8)(g_Game.current->u.field.counter.unsigned_value - 1);
        Area_RunWalk();
    }
}

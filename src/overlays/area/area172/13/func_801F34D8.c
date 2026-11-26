#include "area172_13.h"

MATCH void func_801F34D8(void) {
    s32     pos[3];
    DVECTOR screen;
    MATRIX  camera;
    Actor*  work;
    u8      remaining;

    PushMatrix();
    Camera_SetMatrix(&camera);
    pos[0] = SELF(Actor)->pos.x.fixed;
    pos[1] = SELF(Actor)->pos.y.fixed;
    pos[2] = SELF(Actor)->pos.z.fixed;
    Camera_ProjectPoint(pos, &screen);
    PopMatrix();
    work           = SELF(Actor);
    work->screen_x = screen.vx;
    work->screen_y = screen.vy;
    work->vy -= 16;
    func_801F4138((s16)work->screen_x, (s16)work->screen_y, (s16)work->unk_32, (s16)work->vx, (s16)work->vy);
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        SELF(Actor)->timer = 16;
        SELF(Actor)->header.mode += 1;
    }
}

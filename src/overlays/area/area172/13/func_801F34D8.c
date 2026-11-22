#include "area172_13.h"

MATCH void func_801F34D8(void) {
    s32     pos[3];
    DVECTOR screen;
    MATRIX  camera;
    Actor*  work;
    u8      remaining;

    PushMatrix();
    Camera_SetMatrix(&camera);
    pos[0] = g_Task->pos.x.fixed;
    pos[1] = g_Task->pos.y.fixed;
    pos[2] = g_Task->pos.z.fixed;
    Camera_ProjectPoint(pos, &screen);
    PopMatrix();
    work           = g_Task;
    work->screen_x = screen.vx;
    work->screen_y = screen.vy;
    work->vy -= 16;
    func_801F4138((s16)work->screen_x, (s16)work->screen_y, (s16)work->unk_32, (s16)work->vx, (s16)work->vy);
    ACTOR_COUNT_DOWN(TASK(Actor), remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        g_Task->timer = 16;
        g_Task->header.mode += 1;
    }
}

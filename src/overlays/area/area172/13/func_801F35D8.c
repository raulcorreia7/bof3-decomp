#include "area172_13.h"

MATCH void func_801F35D8(void) {
    s32     pos[3];
    DVECTOR screen;
    MATRIX  camera;
    Actor*  work;
    u8      remaining;

    PushMatrix();
    Area_SetCameraMatrix(&camera);
    pos[0] = g_Task->pos.x.fixed;
    pos[1] = g_Task->pos.y.fixed;
    pos[2] = g_Task->pos.z.fixed;
    Area_ProjectPoint(pos, &screen);
    PopMatrix();
    work           = g_Task;
    work->screen_x = screen.vx;
    work->screen_y = screen.vy;
    work->vx -= 16;
    work->unk_32 -= 20;
    func_801F4138((s16)work->screen_x, (s16)work->screen_y, (s16)work->unk_32, (s16)work->vx, (s16)work->vy);
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        Actor_Clear();
    }
}

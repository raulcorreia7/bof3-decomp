#include "area139_13.h"
#include "shared/etc.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3AD0(void) {
    Actor* task;
    s32    idx;
    s32    delta;
    s32    coord;

    idx                        = g_Task->pos.x.part.integer * 2;
    g_Task->direction_08       = g_Task->pos.y.part.integer == 0;
    g_Task->pos.x.part.integer = D_801F4464[idx];
    g_Task->pos.y.part.integer = D_801F4464[idx + 1];
    g_Task->pos.z.part.integer = FIELD(u16, D_801F445C, idx);
    g_Task->header.step++;
    g_Task->screen_y = 0;
    g_Task->screen_x = FIELD(u16, D_801F4460, idx);
    task             = g_Task;
    if (task->direction_08 != 0) {
        coord = TO_COORD(task->pos.y.part.integer + 1) | COORD_HALF;
        delta = D_80145EC8 - coord;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta > COORD_HALF) {
            goto done;
        }
        delta = D_80145EC4 - TO_COORD(task->pos.x.part.integer);
        if (delta < 0) {
            delta = -delta;
        }
        if (delta > TO_COORD(1)) {
            delta = D_80145EC4 - TO_COORD(task->pos.x.part.integer + 1);
            if (delta < 0) {
                delta = -delta;
            }
            if (delta > TO_COORD(1)) {
                goto done;
            }
        }
    } else {
        coord = TO_COORD(task->pos.x.part.integer + 1) | COORD_HALF;
        delta = D_80145EC4 - coord;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta > COORD_HALF) {
            goto done;
        }
        delta = D_80145EC8 - TO_COORD(task->pos.y.part.integer);
        if (delta < 0) {
            delta = -delta;
        }
        if (delta > TO_COORD(1)) {
            delta = D_80145EC8 - TO_COORD(task->pos.y.part.integer + 1);
            if (delta < 0) {
                delta = -delta;
            }
            if (delta > TO_COORD(1)) {
                goto done;
            }
        }
    }
    task->screen_y    = -0x100;
    task->header.step = 3;

done:
    Area_Update();
}
#else
INCLUDE_ASM(func_801F3AD0);
#endif

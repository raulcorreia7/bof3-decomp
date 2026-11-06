#include "game_00.h"

MATCH void func_8019C124(s32 step_byte) {
    Actor* work;
    s32    vel;

    work = g_Task;
    if (COORD_FRAC(work->pos.x) != 0) {
        vel = work->vx;
        if (vel > 0) {
            if ((step_byte & BYTE_MASK) == 0) {
                work->unk_18 = (work->pos.x.fixed + 0x10000) & 0xFFFF0000;
                goto set_state; /* the x tile advanced by one */
            }
        } else if (vel < 0) {
            /* keep the current tile */
        } else {
            goto set_state; /* the velocity is zero, keep the tile */
        }
        work->unk_18 = work->pos.x.fixed & 0xFFFF0000;
    } else if (COORD_FRAC(work->pos.y) != 0) {
        vel = work->vy;
        if (vel > 0) {
            if ((step_byte & BYTE_MASK) == 0) {
                work->unk_18 = (work->pos.y.fixed + 0x10000) & 0xFFFF0000;
                goto set_state; /* the y tile advanced by one */
            }
        } else if (vel < 0) {
            /* keep the current tile */
        } else {
            goto set_state; /* the velocity is zero, keep the tile */
        }
        work->unk_18 = work->pos.y.fixed & 0xFFFF0000;
    } else {
        return;
    }
set_state:
    g_Task->header.mode = 3;
}

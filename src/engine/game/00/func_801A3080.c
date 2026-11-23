#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801A3080(Actor* actor, s32 facing) {
    Actor* work;
    s32    slot;
    s32    type;
    s8     n;
    u8     dir;
    s16    value;
    s32    angle_x;
    s32    angle_y;
    u16    angle;

    slot    = (s32)(-(((s32)actor - (s32)g_PartyActors) * 0xD79435E5)) >> 3;
    work    = g_Task;
    angle_x = work->angle_x;
    angle_y = work->angle_y;
    type    = facing;
    n       = (s8)slot;
    if (n < 0) {
        n = 4;
    }

    if (g_ActorTurnRamps[n].flags & 1) {
        return;
    }

    dir = type & BYTE_MASK;
    if ((work->vx + work->vy) != 0) {
        value = (s16)(Area_HeightSample(work->pos.x.fixed + g_FacingSteps[dir].x, work->pos.y.fixed + g_FacingStepY[dir * 2]) - COORD_INT(TASK(Actor)->pos.z));
        if (facing & 2) {
            TASK(Actor)->angle_x = 0;
            if (dir != 3) {
                value = -value;
            }
            angle_y = ratan2(value, 0x80);
        } else {
            if (dir != 1) {
                value = -value;
            }
            angle_x              = ratan2(value, 0x80);
            TASK(Actor)->angle_y = 0;
        }
    }

    work = g_Task;
    if (work->timer != 0) {
        g_ActorTurnRamps[n].frames_xy = (s8)(work->timer * 2);
        g_ActorTurnRamps[n].frames_z  = (s8)(TASK(Actor)->unk_0A * 4);
        work                          = g_Task;
        g_ActorTurnRamps[n].delta_x   = (angle_x - work->angle_x) / (work->timer * 2);
        g_ActorTurnRamps[n].delta_y   = (angle_y - work->angle_y) / (work->timer * 2);
        if ((((type - 5) & BYTE_MASK) < 2) && (D_801C842A[0] < (work->angle_z & ANGLE_MASK))) {
            angle = D_801C842A[(facing & BYTE_MASK) - 3] + ONE;
        } else {
            angle = g_ActorFacingAngles[type & BYTE_MASK];
        }
        g_ActorTurnRamps[n].delta_z = ((s16)angle - (TASK(Actor)->angle_z & ANGLE_MASK)) / (TASK(Actor)->unk_0A * 4);
        return;
    }

    g_ActorTurnRamps[n].delta_z = 0;
    g_ActorTurnRamps[n].delta_y = 0;
    g_ActorTurnRamps[n].delta_x = 0;
    work->angle_z               = g_ActorFacingAngles[type & BYTE_MASK];
}
#else
INCLUDE_ASM(func_801A3080);
#endif

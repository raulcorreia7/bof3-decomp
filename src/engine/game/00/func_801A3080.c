#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801A3080(Actor* actor, u8 facing) {
    Actor* work;
    s32    angle_x;
    s32    angle_y;
    s8     n;
    s16    rise;
    u16    angle;

    n       = actor - g_PartyActors;
    work    = TASK(Actor);
    angle_x = work->angle_x;
    angle_y = work->angle_y;
    if (n < 0) {
        n = 4;
    }
    if (g_ActorTurnRamps[n].flags & 1) {
        return;
    }
    if (work->vx + work->vy != 0) {
        rise = Area_HeightSample(work->pos.x.fixed + g_FacingSteps[(u8)facing].x, work->pos.y.fixed + g_FacingSteps[(u8)facing].y) - COORD_INT(TASK(Actor)->pos.z);
        if (facing & 2) {
            {
                s32 slope = rise;

                TASK(Actor)->angle_x = 0;

                if ((u8)facing != 3) {
                    slope = -slope;
                }
                angle_y = ratan2((s16)slope, 0x80);
            }
        } else {
            {
                s32 slope = rise;

                if ((u8)facing != 1) {
                    slope = -slope;
                }
                angle_x = ratan2((s16)slope, 0x80);
            }
            TASK(Actor)->angle_y = 0;
        }
    }
    if (TASK(Actor)->unk_0A != 0) {
        g_ActorTurnRamps[n].frames_xy = TASK(Actor)->unk_0A * 2;
        g_ActorTurnRamps[n].frames_z  = TASK(Actor)->unk_0A * 4;
        work                          = TASK(Actor);
        g_ActorTurnRamps[n].delta_x   = (angle_x - work->angle_x) / (work->unk_0A * 2);
        g_ActorTurnRamps[n].delta_y   = (angle_y - work->angle_y) / (work->unk_0A * 2);
        if ((u8)(facing - 5) < 2 && g_ActorFacingAngles[3] < (work->angle_z & ANGLE_MASK)) {
            angle = g_ActorFacingAngles[(u8)facing] + ONE;
        } else {
            angle = g_ActorFacingAngles[(u8)facing];
        }
        g_ActorTurnRamps[n].delta_z = ((s16)angle - (TASK(Actor)->angle_z & ANGLE_MASK)) / (TASK(Actor)->unk_0A * 4);
        return;
    }
    g_ActorTurnRamps[n].delta_x = g_ActorTurnRamps[n].delta_y = g_ActorTurnRamps[n].delta_z = 0;
    TASK(Actor)->angle_z                                                                    = g_ActorFacingAngles[(u8)facing];
}
#else
INCLUDE_ASM(func_801A3080);
#endif

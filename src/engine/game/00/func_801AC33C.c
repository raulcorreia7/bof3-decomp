#include "game_00.h"

/* Plain scratchpad cell read; emits a fresh absolute load per use. */

MATCH bool func_801AC33C(s32 ease_in, s32 distance) {
    Actor* work;
    s32    step_x;
    s32    step_y;
    s32    delta;
    s32    pos_x;
    s32    pos_y;
    u8     route_index;
    u32    slot;
    s32    index;
    s8     old_a;
    s8     old_b;
    s32    reached_x;
    s32    reached_y;

    work                          = TASK(Actor);
    route_index                   = work->direction & 0x7;
    step_x                        = g_FacingOffsets[route_index].x * g_RouteSpeedScale[g_CurrentActor->unk_78];
    step_y                        = g_FacingOffsets[route_index].y * g_RouteSpeedScale[g_CurrentActor->unk_78];
    reached_y                     = 0;
    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    reached_x                     = 0;
    if ((TASK(Actor)->unk_18 + TASK(Actor)->unk_1C) == 0) {
        g_CurrentActor->walk_dest_x = TASK(Actor)->pos.x.fixed + (g_FacingSteps[TASK(Actor)->direction & 0x7].x << 1) * (distance & BYTE_MASK);
        g_CurrentActor->walk_dest_y = TASK(Actor)->pos.y.fixed + (g_FacingSteps[TASK(Actor)->direction & 0x7].y << 1) * (distance & BYTE_MASK);
        if ((ease_in & BYTE_MASK) != 0) {
            TASK(Actor)->unk_18 = step_x >> (distance & BYTE_MASK);
            TASK(Actor)->unk_1C = step_y >> (distance & BYTE_MASK);
            TASK(Actor)->vx     = 0;
            TASK(Actor)->vy     = 0;
        } else {
            TASK(Actor)->unk_18 = -(step_x >> (distance & BYTE_MASK));
            TASK(Actor)->unk_1C = -(step_y >> (distance & BYTE_MASK));
            TASK(Actor)->vx     = step_x;
            TASK(Actor)->vy     = step_y;
        }
        TASK(Actor)->vz = 0;
    }
    TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
    TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
    TASK(Actor)->vx += TASK(Actor)->unk_18;
    TASK(Actor)->vy += TASK(Actor)->unk_1C;
    delta = TASK(Actor)->vy;
    if (TASK(Actor)->unk_06 == 0x0A) {
        pos_x = TASK(Actor)->pos.x.fixed;
        slot  = (-(((s32)g_CurrentActor - (s32)g_PartyActors) * 0xD79435E5)) >> 3;
        if ((((pos_x ^ (pos_x + TASK(Actor)->vx)) & 0x8000) != 0) || ((pos_y = TASK(Actor)->pos.y.fixed, (((pos_y ^ (pos_y + delta)) & 0x8000)) != 0))) {
            func_801A3080(g_CurrentActor, TASK(Actor)->direction & 0x7);
        }
        index = (s8)slot;
        old_a = g_ActorTurnRamps[index].frames_xy;
        if (old_a != 0) {
            g_ActorTurnRamps[index].frames_xy = old_a - 1;
            TASK(Actor)->angle_x += g_ActorTurnRamps[index].delta_x;
            TASK(Actor)->angle_y += g_ActorTurnRamps[index].delta_y;
        }
        old_b = g_ActorTurnRamps[index].frames_z;
        if (old_b != 0) {
            g_ActorTurnRamps[index].frames_z = old_b - 1;
            TASK(Actor)->angle_z += g_ActorTurnRamps[index].delta_z;
        }
    }
    if (step_x < 0) {
        if (!(TASK(Actor)->pos.x.fixed > g_CurrentActor->walk_dest_x)) {
            reached_x = 1;
        }
    } else {
        if (!(TASK(Actor)->pos.x.fixed < g_CurrentActor->walk_dest_x)) {
            reached_x = 1;
        }
    }
    if (step_y < 0) {
        if (!(TASK(Actor)->pos.y.fixed > g_CurrentActor->walk_dest_y)) {
            reached_y = 1;
        }
    } else {
        if (!(TASK(Actor)->pos.y.fixed < g_CurrentActor->walk_dest_y)) {
            reached_y = 1;
        }
    }
    if ((reached_x & reached_y) != 0) {
        TASK(Actor)->pos.x.fixed = g_CurrentActor->walk_dest_x;
        TASK(Actor)->pos.y.fixed = g_CurrentActor->walk_dest_y;
        TASK(Actor)->vx          = step_x;
        TASK(Actor)->vy          = step_y;
        TASK(Actor)->unk_1C      = 0;
        TASK(Actor)->unk_18      = 0;
        return 0;
    }
    return 1;
}

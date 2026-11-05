#include "game_00.h"

/* Plain scratchpad cell read; emits a fresh absolute load per use. */

MATCH s32 func_801AC33C(s32 ease_in, s32 arg1) {
    Actor* work;
    s32    step_x;
    s32    step_y;
    s32    delta;
    s32    pos_x;
    s32    pos_y;
    u8     route_index;
    u32    slot;
    s32    idx;
    s8     old_a;
    s8     old_b;
    s32    reached_x;
    s32    reached_y;

    work                   = g_Task;
    route_index            = work->direction_08 & 7;
    step_x                 = g_FacingOffsets[route_index].x * g_RouteSpeedScale[g_CurrentActor->unk_78];
    step_y                 = g_FacingOffsets[route_index].y * g_RouteSpeedScale[g_CurrentActor->unk_78];
    reached_y              = 0;
    g_Task->z.part.integer = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    reached_x              = 0;
    if ((g_Task->unk_18 + g_Task->unk_1C) == 0) {
        g_CurrentActor->unk_80 =
            g_Task->x.fixed + (g_FacingSteps[g_Task->direction_08 & 7].x << 1) * (arg1 & BYTE_MASK);
        g_CurrentActor->unk_84 =
            g_Task->y.fixed + (g_FacingSteps[g_Task->direction_08 & 7].y << 1) * (arg1 & BYTE_MASK);
        if ((ease_in & BYTE_MASK) != 0) {
            g_Task->unk_18 = step_x >> (arg1 & BYTE_MASK);
            g_Task->unk_1C = step_y >> (arg1 & BYTE_MASK);
            g_Task->vx     = 0;
            g_Task->vy     = 0;
        } else {
            g_Task->unk_18 = -(step_x >> (arg1 & BYTE_MASK));
            g_Task->unk_1C = -(step_y >> (arg1 & BYTE_MASK));
            g_Task->vx     = step_x;
            g_Task->vy     = step_y;
        }
        g_Task->vz = 0;
    }
    g_Task->x.fixed += g_Task->vx;
    g_Task->y.fixed += g_Task->vy;
    g_Task->vx += g_Task->unk_18;
    g_Task->vy += g_Task->unk_1C;
    delta = g_Task->vy;
    if (g_Task->unk_06 == 0x0A) {
        pos_x = g_Task->x.fixed;
        slot  = (u32)(-(((s32)g_CurrentActor - (s32)D_80147A58) * 0xD79435E5)) >> 3;
        if ((((pos_x ^ (pos_x + g_Task->vx)) & 0x8000) != 0) ||
            ((pos_y = g_Task->y.fixed, (((pos_y ^ (pos_y + delta)) & 0x8000)) != 0))) {
            func_801A3080(g_CurrentActor, g_Task->direction_08 & 7);
        }
        idx   = (s32)(slot << 24) >> 20;
        old_a = D_80147CB9[idx];
        if (old_a != 0) {
            D_80147CB9[idx] = old_a - 1;
            g_Task->unk_64 += FIELD(s32, D_80147CBC, idx);
            g_Task->unk_68 += FIELD(s32, D_80147CC0, idx);
        }
        old_b = D_80147CBA[idx];
        if (old_b != 0) {
            D_80147CBA[idx] = old_b - 1;
            g_Task->unk_6C += FIELD(s32, D_80147CC4, idx);
        }
    }
    if (step_x < 0) {
        if (!(g_Task->x.fixed > g_CurrentActor->unk_80)) {
            reached_x = 1;
        }
    } else {
        if (!(g_Task->x.fixed < g_CurrentActor->unk_80)) {
            reached_x = 1;
        }
    }
    if (step_y < 0) {
        if (!(g_Task->y.fixed > g_CurrentActor->unk_84)) {
            reached_y = 1;
        }
    } else {
        if (!(g_Task->y.fixed < g_CurrentActor->unk_84)) {
            reached_y = 1;
        }
    }
    if ((reached_x & reached_y) != 0) {
        g_Task->x.fixed = g_CurrentActor->unk_80;
        g_Task->y.fixed = g_CurrentActor->unk_84;
        g_Task->vx      = step_x;
        g_Task->vy      = step_y;
        g_Task->unk_1C  = 0;
        g_Task->unk_18  = 0;
        return 0;
    }
    return 1;
}

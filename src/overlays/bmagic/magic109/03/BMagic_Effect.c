#include "magic109_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

MATCH void func_801EEC80(void) {
    RECT         rect;
    PartyMember* work;

    if (g_Battle.target_selector == 0x80 && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Task->header.mode = 1;
    }
    if (g_Battle.target_selector == 0x40 && !(g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT)) {
        g_Task->header.mode = 1;
    }
    if (g_Task->header.mode != 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->unk_09 = 2;
    work           = g_Task;
    rect.x         = work->unk_2E.half - work->unk_09;
    rect.y         = work->unk_30.half - work->unk_09 + g_FrameBufferIndex * 240;
    rect.h = rect.w = work->unk_09 * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x340, 0x100);
    GFX_AddPrim(3, sizeof(DR_MOVE));
    if (g_Battle.target_selector & 0x40) {
        g_Task->unk_2E.half = D_801EF9D8[g_Battle.scroll_dir].x;
        g_Task->unk_30.half = D_801EF9D8[g_Battle.scroll_dir].y;
    } else {
        g_Task->unk_2E.half = D_801EF9D8[g_Battle.scroll_dir ^ 2].x;
        g_Task->unk_30.half = D_801EF9D8[g_Battle.scroll_dir ^ 2].y;
    }
    g_Task->unk_64 = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEEAC(void) {
    u8 count;

    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x54) {
        g_Task->header.mode += 1;
        g_Task->timer = 64;
    }
    func_801EF0F8(g_Task->unk_64);
}

MATCH void func_801EEF30(void) {
    s32 raised_offset;
    s32 lowered_offset;
    u8  timer;

    timer         = g_Task->timer;
    g_Task->timer = timer + 0xFF;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->header.mode += 1;
    }
    func_801EF0F8(g_Task->unk_64);
    if (g_Task->param.unk_0B == 0) {
        raised_offset  = g_Task->unk_64 + 8;
        g_Task->unk_64 = raised_offset;
        if (raised_offset >= 0x80) {
            g_Task->param.unk_0B = 1;
        }
    } else {
        lowered_offset = g_Task->unk_64 - 8;
        g_Task->unk_64 = lowered_offset;
        if (lowered_offset < -0x7F) {
            g_Task->param.unk_0B = 0;
        }
    }
}

MATCH void func_801EF008(void) {
    u8  timer;
    s32 offset;

    timer          = g_Task->unk_09 - 2;
    g_Task->unk_09 = timer;
    if (timer == 2) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    func_801EF0F8(g_Task->unk_64);
    if (g_Task->param.unk_0B == 0) {
        offset         = g_Task->unk_64 + 8;
        g_Task->unk_64 = offset;
        if (offset >= 0x80) {
            g_Task->param.unk_0B = 1;
        }
    } else {
        offset         = g_Task->unk_64 - 8;
        g_Task->unk_64 = offset;
        if (offset < -0x7F) {
            g_Task->param.unk_0B = 0;
        }
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF0F8(s32 offset) {
    s16          move_x;
    s16          move_y;
    s16          move_width;
    s16          move_height;
    s32          effect_offset;
    s32          ring_angle;
    s32          outer_ring;
    Point2l*     spiral_point;
    Point2l*     rim_point;
    s16          quad_y0;
    s16          quad_x1;
    s16          quad_y1;
    s16          quad_x2;
    s16          quad_y2;
    s16          quad_x3;
    s16          quad_y3;
    s16          quad_x1_reversed;
    s16          quad_y1_reversed;
    s16          quad_x0_reversed;
    s16          quad_y0_reversed;
    s16          quad_x3_reversed;
    s16          quad_y3_reversed;
    s16          quad_x2_reversed;
    s16          quad_y2_reversed;
    s16          diameter;
    s16          quad_x0;
    s16          quad_tpage;
    s32          outer_vertex;
    s32          outer_next_vertex;
    s32          outer_vertex_reversed;
    s32          outer_next_vertex_reversed;
    s32          column;
    s32          inner_vertex;
    s32          column_reversed;
    s32          inner_vertex_reversed;
    s32          next_column;
    s32          inner_next_vertex;
    s32          next_column_reversed;
    s32          inner_next_vertex_reversed;
    s32          vertex;
    s32          spiral_angle;
    s32          mesh_angle;
    s32          rim_angle;
    s32          row_offset;
    s32          outer_row_offset;
    s32          next_ring;
    s32          rim_y;
    s32          spiral_y;
    s32          rim_y_reversed;
    s32          spiral_y_reversed;
    s32          draw_tpage;
    s8           next_row;
    s8           next_quad;
    s8           next_entry;
    s8           next_segment;
    s8           next_rim_segment;
    s8           lower_ring;
    s8           next_spiral_segment;
    s8           outer_shade;
    s8           inner_shade;
    s8           segment;
    s8           spiral_segment;
    s8           quad;
    s8           entry;
    s8           row;
    s8           rim_segment;
    s8           ring;
    POLY_GT4*    poly_gt4;
    POLY_F4*     poly_f4;
    PartyMember* quad_task;
    PartyMember* mesh_task;

    row           = 0;
    effect_offset = offset;
    ring_angle    = 0;
    do {
        segment = 0;
    mesh_loop:
        mesh_angle           = segment << 8;
        vertex               = segment + (row << 4);
        D_801EFAF8[vertex].x = FIXED_MUL(rsin(mesh_angle), row * (g_Task->unk_09 >> 3));
        mesh_task            = g_Task;
        next_segment         = segment + 1;
        segment              = next_segment;
        D_801EFAF8[vertex].y = FIXED_MUL(rcos(mesh_angle), row * (mesh_task->unk_09 >> 3));
        next_row                  = row + 1;
        if (next_segment < 0x10) {
            goto mesh_loop;
        }
        row = next_row;
    } while (next_row < 9);
    move_x      = mesh_task->unk_2E.half - mesh_task->unk_09;
    move_y      = (mesh_task->unk_30.half - mesh_task->unk_09) + (g_FrameBufferIndex * 0xF0);
    diameter    = mesh_task->unk_09 * 2;
    move_width  = diameter;
    move_height = diameter;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, (RECT*)&move_x, 0x340, 0x100);
    GFX_AddPrim(3U, 0x18U);
    draw_tpage = 0x42D;
    if (GetGraphType() != 1) {
        draw_tpage = 0x11D;
        if (GetGraphType() == 2) {
            draw_tpage = 0x42D;
        }
    }
    rim_segment = 0;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, draw_tpage, NULL);
    GFX_AddPrim(3U, 0xCU);
    do {
        rim_angle                    = rim_segment << 8;
        D_801EF9F8[rim_segment].x    = FIXED_MUL(rsin(rim_angle), g_Task->unk_09);
        next_rim_segment             = rim_segment + 1;
        D_801EF9F8[rim_segment].y    = FIXED_MUL(rcos(rim_angle), g_Task->unk_09);
        rim_segment                  = next_rim_segment;
    } while (next_rim_segment < 0x10);
    ring = 7;
    do {
        spiral_segment = 0;
        ring_angle += effect_offset * (8 - ring);
    spiral_loop:
        spiral_angle                 = ring_angle + (spiral_segment << 8);
        D_801EFA78[spiral_segment].x = FIXED_MUL(rsin(spiral_angle), ring * (g_Task->unk_09 >> 3));
        next_spiral_segment          = spiral_segment + 1;
        D_801EFA78[spiral_segment].y = FIXED_MUL(rcos(spiral_angle), ring * (g_Task->unk_09 >> 3));
        spiral_segment               = next_spiral_segment;
        if (next_spiral_segment < 0x10) {
            goto spiral_loop;
        }
        rim_point        = D_801EF9F8;
        spiral_point     = D_801EFA78;
        quad             = 0;
        next_ring        = ring + 1;
        outer_ring       = next_ring;
        outer_row_offset = next_ring << 4;
        row_offset       = ring << 4;
    quad_loop:
        poly_f4 = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4((POLY_F4*)poly_f4);
        poly_f4->r0 = 0;
        poly_f4->g0 = 0;
        poly_f4->b0 = 0;
        poly_gt4    = (POLY_GT4*)(g_GfxPrimCursor + 0x18);
        SetPolyGT4((POLY_GT4*)poly_gt4);
        quad_tpage = 0x42D;
        if (GetGraphType() != 1) {
            quad_tpage = 0x11D;
            if (GetGraphType() == 2) {
                quad_tpage = 0x42D;
            }
        }
        outer_shade     = outer_ring * 0x10;
        poly_gt4->r0    = outer_shade;
        poly_gt4->g0    = outer_shade;
        poly_gt4->b0    = outer_shade;
        poly_gt4->r1    = outer_shade;
        poly_gt4->g1    = outer_shade;
        poly_gt4->b1    = outer_shade;
        inner_shade     = ring * 0x10;
        poly_gt4->r2    = inner_shade;
        poly_gt4->g2    = inner_shade;
        poly_gt4->b2    = inner_shade;
        poly_gt4->r3    = inner_shade;
        poly_gt4->g3    = inner_shade;
        poly_gt4->b3    = inner_shade;
        quad_task       = g_Task;
        poly_gt4->tpage = quad_tpage;
        if (quad_task->unk_64 > 0) {
            next_column  = ((quad + 1) & 0xF);
            quad_x0      = quad_task->unk_2E.half + rim_point->x;
            poly_gt4->x0 = quad_x0;
            poly_f4->x0  = quad_x0;
            rim_y         = rim_point->y;
            rim_point     = &D_801EF9F8[next_column];
            quad_y0       = quad_task->unk_30.half + rim_y;
            poly_gt4->y0  = quad_y0;
            poly_f4->y0   = quad_y0;
            quad_x1       = quad_task->unk_2E.half + rim_point->x;
            poly_gt4->x1  = quad_x1;
            poly_f4->x1   = quad_x1;
            quad_y1       = quad_task->unk_30.half + rim_point->y;
            poly_gt4->y1  = quad_y1;
            poly_f4->y1   = quad_y1;
            quad_x2       = quad_task->unk_2E.half + spiral_point->x;
            poly_gt4->x2  = quad_x2;
            poly_f4->x2   = quad_x2;
            spiral_y      = spiral_point->y;
            spiral_point  = &D_801EFA78[next_column];
            quad_y2       = quad_task->unk_30.half + spiral_y;
            poly_gt4->y2  = quad_y2;
            poly_f4->y2   = quad_y2;
            column        = quad & 0xF;
            quad_x3       = quad_task->unk_2E.half + spiral_point->x;
            poly_gt4->x3  = quad_x3;
            poly_f4->x3   = quad_x3;
            outer_vertex  = column + outer_row_offset;
            quad_y3       = quad_task->unk_30.half + spiral_point->y;
            poly_gt4->y3  = quad_y3;
            poly_f4->y3   = quad_y3;
            poly_gt4->u0  = (s8)(quad_task->unk_09 + D_801EFAF8[outer_vertex].x);
            outer_next_vertex = next_column + outer_row_offset;
            poly_gt4->v0      = (s8)((g_Task)->unk_09 + D_801EFAF8[outer_vertex].y);
            poly_gt4->u1      = (s8)((g_Task)->unk_09 + D_801EFAF8[outer_next_vertex].x);
            inner_vertex      = column + row_offset;
            poly_gt4->v1      = (s8)((g_Task)->unk_09 + D_801EFAF8[outer_next_vertex].y);
            poly_gt4->u2      = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_vertex].x);
            inner_next_vertex = next_column + row_offset;
            poly_gt4->v2      = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_vertex].y);
            poly_gt4->u3      = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_next_vertex].x);
            poly_gt4->v3      = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_next_vertex].y);
        } else {
            next_column_reversed = ((quad + 1) & 0xF);
            quad_x1_reversed     = quad_task->unk_2E.half + rim_point->x;
            poly_gt4->x1         = quad_x1_reversed;
            poly_f4->x1          = quad_x1_reversed;
            rim_y_reversed       = rim_point->y;
            rim_point            = &D_801EF9F8[next_column_reversed];
            quad_y1_reversed     = quad_task->unk_30.half + rim_y_reversed;
            poly_gt4->y1         = quad_y1_reversed;
            poly_f4->y1          = quad_y1_reversed;
            quad_x0_reversed     = quad_task->unk_2E.half + rim_point->x;
            poly_gt4->x0         = quad_x0_reversed;
            poly_f4->x0          = quad_x0_reversed;
            quad_y0_reversed     = quad_task->unk_30.half + rim_point->y;
            poly_gt4->y0         = quad_y0_reversed;
            poly_f4->y0          = quad_y0_reversed;
            quad_x3_reversed     = quad_task->unk_2E.half + spiral_point->x;
            poly_gt4->x3         = quad_x3_reversed;
            poly_f4->x3          = quad_x3_reversed;
            spiral_y_reversed    = spiral_point->y;
            spiral_point         = &D_801EFA78[next_column_reversed];
            quad_y3_reversed     = quad_task->unk_30.half + spiral_y_reversed;
            poly_gt4->y3         = quad_y3_reversed;
            poly_f4->y3          = quad_y3_reversed;
            column_reversed      = quad & 0xF;
            quad_x2_reversed     = quad_task->unk_2E.half + spiral_point->x;
            poly_gt4->x2         = quad_x2_reversed;
            poly_f4->x2          = quad_x2_reversed;
            outer_vertex_reversed = column_reversed + outer_row_offset;
            quad_y2_reversed      = quad_task->unk_30.half + spiral_point->y;
            poly_gt4->y2          = quad_y2_reversed;
            poly_f4->y2           = quad_y2_reversed;
            poly_gt4->u1          = (s8)(quad_task->unk_09 + D_801EFAF8[outer_vertex_reversed].x);
            outer_next_vertex_reversed = next_column_reversed + outer_row_offset;
            poly_gt4->v1               = (s8)((g_Task)->unk_09 + D_801EFAF8[outer_vertex_reversed].y);
            poly_gt4->u0               = (s8)((g_Task)->unk_09 + D_801EFAF8[outer_next_vertex_reversed].x);
            inner_vertex_reversed      = column_reversed + row_offset;
            poly_gt4->v0               = (s8)((g_Task)->unk_09 + D_801EFAF8[outer_next_vertex_reversed].y);
            poly_gt4->u3               = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_vertex_reversed].x);
            inner_next_vertex_reversed = next_column_reversed + row_offset;
            poly_gt4->v3               = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_vertex_reversed].y);
            poly_gt4->u2               = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_next_vertex_reversed].x);
            poly_gt4->v2               = (s8)((g_Task)->unk_09 + D_801EFAF8[inner_next_vertex_reversed].y);
        }
        GFX_AddPrim(3U, 0x18U);
        GFX_AddPrim(3U, 0x34U);
        next_quad = quad + 1;
        quad      = next_quad;
        if (next_quad < 0x10) {
            goto quad_loop;
        }
        entry = 0;
    copy_loop:
        D_801EF9F8[entry].x = D_801EFA78[entry].x;
        D_801EF9F8[entry].y = D_801EFA78[entry].y;
        next_entry          = entry + 1;
        entry               = next_entry;
        if (next_entry < 0x10) {
            goto copy_loop;
        }
        lower_ring = ring - 1;
        ring       = lower_ring;
    } while (!(lower_ring & 0x80));
}
#else
INCLUDE_ASM(func_801EF0F8);
#endif

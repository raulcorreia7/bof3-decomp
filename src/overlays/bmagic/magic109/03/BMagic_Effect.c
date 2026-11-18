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
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
        return;
    }
    SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0));
    g_Task->unk_09 = 2;
    work           = g_Task;
    rect.x         = work->unk_2E.value - work->unk_09;
    rect.y         = work->unk_30.value - work->unk_09 + g_GfxBufferIndex * 240;
    rect.h = rect.w = work->unk_09 * 2;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x340, 0x100);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MOVE));
    if (g_Battle.target_selector & 0x40) {
        g_Task->unk_2E.value = D_801EF9D8[g_Battle.scroll_dir].x;
        g_Task->unk_30.value = D_801EF9D8[g_Battle.scroll_dir].y;
    } else {
        g_Task->unk_2E.value = D_801EF9D8[g_Battle.scroll_dir ^ 2].x;
        g_Task->unk_30.value = D_801EF9D8[g_Battle.scroll_dir ^ 2].y;
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
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
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
    RECT         move;
    s32          ring_angle;
    s32          outer_ring;
    s16          quad_y0;
    s16          quad_x1;
    s16          quad_y1;
    s16          quad_x2;
    s16          quad_y2;
    s16          quad_x3;
    s16          quad_y3;
    s16          diameter;
    s16          quad_x0;
    s32          outer_vertex;
    s32          outer_next_vertex;
    s32          inner_vertex;
    s32          next_column;
    s32          inner_next_vertex;
    s32          vertex;
    s32          spiral_angle;
    s32          mesh_angle;
    s32          rim_angle;
    s32          row_offset;
    s32          outer_row_offset;
    s32          next_ring;
    s32          first;
    s32          second;
    s32          mesh_tpage;
    s8           outer_shade;
    s8           inner_shade;
    s8           segment;
    s8           quad;
    s8           entry;
    s8           row;
    s8           ring;
    POLY_GT4*    poly_gt4;
    POLY_F4*     poly_f4;
    PartyMember* quad_task;
    PartyMember* mesh_task;

    ring_angle = 0;
    for (row = 0; row < 9; row++) {
        for (segment = 0; segment < 16; segment++) {
            mesh_angle           = segment << 8;
            vertex               = segment + (row << 4);
            D_801EFAF8[vertex].x = FIXED_MUL(rsin(mesh_angle), row * (g_Task->unk_09 >> 3));
            D_801EFAF8[vertex].y = FIXED_MUL(rcos(mesh_angle), row * (g_Task->unk_09 >> 3));
        }
    }
    mesh_task = g_Task;
    move.x    = mesh_task->unk_2E.value - mesh_task->unk_09;
    move.y    = (mesh_task->unk_30.value - mesh_task->unk_09) + (g_GfxBufferIndex * SCREEN_HEIGHT);
    diameter  = mesh_task->unk_09 * 2;
    move.h = move.w = diameter;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &move, 0x340, 0x100);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MOVE));
    /* The mesh's page at VRAM (832, 256), in the encoding the current graph type reads. */
    mesh_tpage = getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_HALF, 832, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, mesh_tpage);
    for (segment = 0; segment < 16; segment++) {
        rim_angle             = segment << 8;
        D_801EF9F8[segment].x = FIXED_MUL(rsin(rim_angle), g_Task->unk_09);
        D_801EF9F8[segment].y = FIXED_MUL(rcos(rim_angle), g_Task->unk_09);
    }
    for (ring = 7; ring >= 0; ring--) {
        ring_angle += offset * (8 - ring);
        for (segment = 0; segment < 16; segment++) {
            spiral_angle          = ring_angle + (segment << 8);
            D_801EFA78[segment].x = FIXED_MUL(rsin(spiral_angle), ring * (g_Task->unk_09 >> 3));
            D_801EFA78[segment].y = FIXED_MUL(rcos(spiral_angle), ring * (g_Task->unk_09 >> 3));
        }
        next_ring        = ring + 1;
        outer_ring       = next_ring;
        outer_row_offset = next_ring << 4;
        row_offset       = ring << 4;
        for (quad = 0; quad < 16; quad++) {
            poly_f4 = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4((POLY_F4*)poly_f4);
            setRGB0(poly_f4, 0, 0, 0);
            poly_gt4 = (POLY_GT4*)(g_GfxPrimCursor + sizeof(POLY_F4));
            SetPolyGT4((POLY_GT4*)poly_gt4);
            outer_shade = outer_ring * 0x10;
            setRGB0(poly_gt4, outer_shade, outer_shade, outer_shade);
            setRGB1(poly_gt4, outer_shade, outer_shade, outer_shade);
            inner_shade = ring * 0x10;
            setRGB2(poly_gt4, inner_shade, inner_shade, inner_shade);
            setRGB3(poly_gt4, inner_shade, inner_shade, inner_shade);
            poly_gt4->tpage = mesh_tpage;
            quad_task       = g_Task;
            next_column     = (quad + 1) & 0xF;
            if (quad_task->unk_64 > 0) {
                first  = quad;
                second = next_column;
            } else {
                first  = next_column;
                second = quad;
            }
            quad_x0           = quad_task->unk_2E.value + D_801EF9F8[first].x;
            poly_gt4->x0      = quad_x0;
            poly_f4->x0       = quad_x0;
            quad_y0           = quad_task->unk_30.value + D_801EF9F8[first].y;
            poly_gt4->y0      = quad_y0;
            poly_f4->y0       = quad_y0;
            quad_x1           = quad_task->unk_2E.value + D_801EF9F8[second].x;
            poly_gt4->x1      = quad_x1;
            poly_f4->x1       = quad_x1;
            quad_y1           = quad_task->unk_30.value + D_801EF9F8[second].y;
            poly_gt4->y1      = quad_y1;
            poly_f4->y1       = quad_y1;
            quad_x2           = quad_task->unk_2E.value + D_801EFA78[first].x;
            poly_gt4->x2      = quad_x2;
            poly_f4->x2       = quad_x2;
            quad_y2           = quad_task->unk_30.value + D_801EFA78[first].y;
            poly_gt4->y2      = quad_y2;
            poly_f4->y2       = quad_y2;
            quad_x3           = quad_task->unk_2E.value + D_801EFA78[second].x;
            poly_gt4->x3      = quad_x3;
            poly_f4->x3       = quad_x3;
            quad_y3           = quad_task->unk_30.value + D_801EFA78[second].y;
            poly_gt4->y3      = quad_y3;
            poly_f4->y3       = quad_y3;
            outer_vertex      = first + outer_row_offset;
            outer_next_vertex = second + outer_row_offset;
            inner_vertex      = first + row_offset;
            inner_next_vertex = second + row_offset;
            setUV4(poly_gt4, quad_task->unk_09 + D_801EFAF8[outer_vertex].x, quad_task->unk_09 + D_801EFAF8[outer_vertex].y, quad_task->unk_09 + D_801EFAF8[outer_next_vertex].x,
                   quad_task->unk_09 + D_801EFAF8[outer_next_vertex].y, quad_task->unk_09 + D_801EFAF8[inner_vertex].x, quad_task->unk_09 + D_801EFAF8[inner_vertex].y,
                   quad_task->unk_09 + D_801EFAF8[inner_next_vertex].x, quad_task->unk_09 + D_801EFAF8[inner_next_vertex].y);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_F4));
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
        }
        for (entry = 0; entry < 16; entry++) {
            D_801EF9F8[entry].x = D_801EFA78[entry].x;
            D_801EF9F8[entry].y = D_801EFA78[entry].y;
        }
    }
}
#else
INCLUDE_ASM(func_801EF0F8);
#endif

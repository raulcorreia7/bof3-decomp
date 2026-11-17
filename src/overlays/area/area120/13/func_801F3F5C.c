#include "area120_13.h"

#define AREA_EFFECT_PART_TAG  (0xBF00u << 16)
#define AREA_EFFECT_PART_TILE 0x9111u
#define AREA_EFFECT_PART_WORD (AREA_EFFECT_PART_TAG | AREA_EFFECT_PART_TILE)

#ifdef NON_MATCHING
NON_MATCHING void func_801F3F5C(s32 part, s32 span, s32 phase_step, s32 offset) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    u32       row;
    u32       next_row;
    u32       indices[2];
    u32       part_words[2];
    s32       x;
    s32       y;
    s32       step;
    s32       height;
    s32       next_y;
    s32       tpage;
    s16*      row2_y;
    s16*      row3_y;

    row  = g_Task->unk_0A;
    step = span;
    row += phase_step;
    g_Task->unk_0A = row;
    row            = g_Task->unk_0A;
    if (row < 12U) {
        next_row = row;
    } else {
        next_row = row - 12;
    }
    g_Task->unk_0A = next_row;

    row        = g_Task->unk_0A >> 1;
    indices[0] = row;
    indices[1] = row + 2;
    if (indices[1] >= 6U) {
        indices[1] = row - 4;
    }

    part_words[0] = row;
    part_words[1] = indices[1];
    for (i = 0; i < 2; i++) {
        part_words[i] += ((u32)part << 16) | AREA_EFFECT_PART_WORD;
    }

    y      = ((g_Task->pos.y.part.integer - 0x80) << 7) + 0x10;
    x      = ((g_Task->pos.x.part.integer - 0x80) << 7) + 0x10;
    row2_y = &g_ScratchPadVectors[2].vy;
    row3_y = &g_ScratchPadVectors[3].vy;

    for (i = 0; i < 2; i++) {
        if (GetGraphType() == 1 || GetGraphType() == 2) {
            tpage = 0x225;
        } else {
            tpage = 0x95;
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, NULL);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, 0xC);
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);

        g_ScratchPadVectors[0].vx = x;
        g_ScratchPadVectors[2].vx = x;
        g_ScratchPadVectors[1].vx = x - i * step;
        g_ScratchPadVectors[3].vx = x - i * step;
        next_y                    = y + step;
        if (i == 0) {
            g_ScratchPadVectors[0].vy = y + step - offset;
            g_ScratchPadVectors[1].vy = y - step - offset;
            *row2_y                   = y;
            *row3_y                   = next_y;
        } else {
            g_ScratchPadVectors[0].vy = y - offset;
            g_ScratchPadVectors[1].vy = y - offset;
            *row2_y                   = y;
            *row3_y                   = y;
        }

        height                    = -Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) / 2;
        g_ScratchPadVectors[0].vz = height - ((step * 2) + 0xC0);
        g_ScratchPadVectors[1].vz = height - ((step * 2) + 0xC0);
        height                    = -Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) / 2;
        g_ScratchPadVectors[2].vz = height - 0xC0;
        g_ScratchPadVectors[3].vz = height - 0xC0;

        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(part_words[i], prim, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, 0x28);
    }
}
#else
INCLUDE_ASM(func_801F3F5C);
#endif

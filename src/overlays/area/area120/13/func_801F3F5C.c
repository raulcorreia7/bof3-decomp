#include "area120_13.h"

#define AREA_EFFECT_PART_TAG  (0xBF00u << 16)
#define AREA_EFFECT_PART_TILE 0x9111u
#define AREA_EFFECT_PART_WORD (AREA_EFFECT_PART_TAG | AREA_EFFECT_PART_TILE)

/* Draws the two ground quads of a field-effect part at the task's position: each
 * one projects the four scratchpad corners and queues a textured tile. The task's
 * phase byte advances by phase_step and wraps at twelve; halved, it picks the two
 * tiles of the pair, the second one two rows on and wrapping at six. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F3F5C(s32 part, s32 span, s32 phase_step, s32 offset) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    u32       part_words[2];
    s32       x;
    s32       y;
    s32       tpage;
    u32       row;
    u32       next_row;
    s32       i;
    s32       height;
    s16*      vy_top;
    s16*      vy_bottom;

    row                 = TASK(Actor)->unk_0A + phase_step;
    TASK(Actor)->unk_0A = row;

    row = TASK(Actor)->unk_0A;
    if (row < 12U) {
        next_row = row;
    } else {
        next_row = row - 12;
    }
    TASK(Actor)->unk_0A = next_row;

    row           = TASK(Actor)->unk_0A >> 1;
    part_words[0] = row;
    if (row + 2 < 6U) {
        part_words[1] = row + 2;
    } else {
        part_words[1] = row - 4;
    }
    for (i = 0; i < 2; i++) {
        part_words[i] += ((u32)part << 16) | AREA_EFFECT_PART_WORD;
    }

    y = ((TASK(Actor)->pos.y.part.integer - 0x80) << 7) + 0x10;

    vy_top    = &g_ScratchPadVectors[2].vy;
    vy_bottom = &g_ScratchPadVectors[3].vy;
    x         = ((TASK(Actor)->pos.x.part.integer - 0x80) << 7) + 0x10;

    for (i = 0; i < 2; i++) {
        tpage = getTPage(1, 0, 320, 256);
        GFX_SET_DRAW_MODE(tpage);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, 0xC);
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);

        g_ScratchPadVectors[2].vx = x + i * span;
        g_ScratchPadVectors[0].vx = x + i * span;
        g_ScratchPadVectors[3].vx = x - i * span;
        g_ScratchPadVectors[1].vx = x - i * span;
        if (i == 0) {
            g_ScratchPadVectors[0].vy = (y + span) - offset;
        } else {
            g_ScratchPadVectors[0].vy = y - offset;
        }
        if (i == 0) {
            *vy_top                   = y + span;
            g_ScratchPadVectors[1].vy = (y - span) - offset;
            *vy_bottom                = y - span;
        } else {
            *vy_top                   = y;
            g_ScratchPadVectors[1].vy = y - offset;
            *vy_bottom                = y;
        }

        height                    = -Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) / 2;
        g_ScratchPadVectors[0].vz = height - ((span * 2) + 0xC0);
        g_ScratchPadVectors[1].vz = height - ((span * 2) + 0xC0);
        height                    = -Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) / 2;
        g_ScratchPadVectors[2].vz = height - 0xC0;
        g_ScratchPadVectors[3].vz = height - 0xC0;

        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(part_words[i], prim, 1);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, 0x28);
    }
}
#else
INCLUDE_ASM(func_801F3F5C);
#endif

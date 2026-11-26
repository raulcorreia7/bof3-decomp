#include "area120_13.h"

#define AREA_EFFECT_PART_TAG  (0xBF00u << 16)
#define AREA_EFFECT_PART_TILE 0x9111u
#define AREA_EFFECT_PART_WORD (AREA_EFFECT_PART_TAG | AREA_EFFECT_PART_TILE)

/* Draws the two ground quads of a field-effect part at the task's position: each
 * one projects the four scratchpad corners and queues a textured tile. The task's
 * phase byte advances by phase_step and wraps at twelve; halved, it picks the two
 * tiles of the pair, the second one two rows on and wrapping at six. */
MATCH void func_801F3F5C(s32 part, s32 span, s32 phase_step, s32 offset) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    u32       part_words[2];
    s32       x;
    s32       y;
    s32       tpage;
    s32       i;

    SELF(Actor)->unk_0A += phase_step;
    SELF(Actor)->unk_0A = (SELF(Actor)->unk_0A < 12) ? SELF(Actor)->unk_0A : SELF(Actor)->unk_0A - 12;
    part_words[0]       = SELF(Actor)->unk_0A >> 1;
    part_words[1]       = (part_words[0] + 2 < 6U) ? part_words[0] + 2 : part_words[0] - 4;
    for (i = 0; i < 2; i++) {
        part_words[i] = (((u32)part << 16) | AREA_EFFECT_PART_WORD) + part_words[i];
    }

    y = ((SELF(Actor)->pos.y.part.integer - 0x80) << 7) + 0x10;
    x = ((SELF(Actor)->pos.x.part.integer - 0x80) << 7) + 0x10;
    for (i = 0; i < 2; i++) {
        tpage = getTPage(1, 0, 320, 256);
        GFX_SET_DRAW_MODE(tpage);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, 0xC);
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);

        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = x + i * span;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = x - i * span;
        g_ScratchPadVectors[0].vy                             = (i == 0) ? y + span - offset : y - offset;
        g_ScratchPadVectors[2].vy                             = (i == 0) ? y + span : y;
        g_ScratchPadVectors[1].vy                             = (i == 0) ? y - span - offset : y - offset;
        g_ScratchPadVectors[3].vy                             = (i == 0) ? y - span : y;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = -(s16)Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) / 2 - (s16)(span * 2 + 0xC0);
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = -(s16)Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) / 2 - 0xC0;

        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(part_words[i], prim, 1);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, 0x28);
    }
}

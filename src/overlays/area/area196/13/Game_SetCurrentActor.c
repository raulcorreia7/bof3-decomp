#include "area196_13.h"

/* Draws the current actor's spinning cone: sixteen rotated copies of a tapered ring of twisted gouraud quads, each with a back quad, and two depth-scaled sprites per copy. */
MATCH void Game_SetCurrentActor(s32 tint) {
    s32       row;
    s32       i;
    s32       size;
    s32       angle;
    POLY_GT4* quad;
    POLY_GT4* back;
    long      p;
    long      flag;

    /* The scratchpad screen pair: the actor's projected x and y at +0x00, the projected rim point at +0x0C. */
    row           = 0;
    D_1F800034[0] = (SELF(PartyMember)->pos.x.fixed >> 9) - 0x4000;
    D_1F800034[1] = (SELF(PartyMember)->pos.y.fixed >> 9) - 0x4000;

    for (; row < 16; row++) {
        for (i = 7; i >= 0; i--) {
            quad = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyGT4(quad);
            SetSemiTrans(quad, 1);
            g_ScratchPadVectors[0].vx = (u16)D_1F800034[0] + (rsin(row << 8) >> 8) * D_801F4150[i];
            g_ScratchPadVectors[0].vy = (u16)D_1F800034[1] + (rcos(row << 8) >> 8) * D_801F4150[i];
            g_ScratchPadVectors[0].vz = -(D_801F415C[i] << 5);
            g_ScratchPadVectors[1].vx = (u16)D_1F800034[0] + (rsin((row + 1) << 8) >> 8) * D_801F4150[i];
            g_ScratchPadVectors[1].vy = (u16)D_1F800034[1] + (rcos((row + 1) << 8) >> 8) * D_801F4150[i];
            g_ScratchPadVectors[1].vz = -(D_801F415C[i] << 5);
            g_ScratchPadVectors[2].vx = (u16)D_1F800034[0] + (rsin(row << 8) >> 8) * D_801F4150[i + 1];
            g_ScratchPadVectors[2].vy = (u16)D_1F800034[1] + (rcos(row << 8) >> 8) * D_801F4150[i + 1];
            g_ScratchPadVectors[2].vz = -(D_801F415C[i + 1] << 5);
            g_ScratchPadVectors[3].vx = (u16)D_1F800034[0] + (rsin((row + 1) << 8) >> 8) * D_801F4150[i + 1];
            g_ScratchPadVectors[3].vy = (u16)D_1F800034[1] + (rcos((row + 1) << 8) >> 8) * D_801F4150[i + 1];
            g_ScratchPadVectors[3].vz = -(D_801F415C[i + 1] << 5);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&quad->x0, (long*)&quad->x1, (long*)&quad->x2, (long*)&quad->x3,
                          &p, &flag);
            setUV4(quad, 0xB0, 0x20, 0xCF, 0x20, 0xB0, 0x3F, 0xCF, 0x3F);
            quad->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0x325 : 0xD5;
            quad->clut  = getClut(0, 485);
            setRGB0(quad, D_801F412C[i], D_801F412C[i], D_801F412C[i]);
            setRGB1(quad, D_801F412C[i], D_801F412C[i], D_801F412C[i]);
            setRGB2(quad, D_801F412C[i + 1], D_801F412C[i + 1], D_801F412C[i + 1]);
            setRGB3(quad, D_801F412C[i + 1], D_801F412C[i + 1], D_801F412C[i + 1]);
            Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, (s8)D_801F4168[row], sizeof(POLY_GT4));

            /* The back quad reuses the projected corners and texture with its own palette and blend mode. */
            back = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyGT4(back);
            SetShadeTex(back, 0);
            SetSemiTrans(back, 1);
            *(long*)&back->x0 = *(long*)&quad->x0;
            *(long*)&back->x1 = *(long*)&quad->x1;
            *(long*)&back->x2 = *(long*)&quad->x2;
            *(long*)&back->x3 = *(long*)&quad->x3;
            setUV4(back, 0xB0, 0x20, 0xCF, 0x20, 0xB0, 0x3F, 0xCF, 0x3F);
            back->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5;
            back->clut  = getClut(0, 484);
            setRGB0(back, D_801F412C[i], D_801F412C[i], D_801F412C[i]);
            setRGB1(back, D_801F412C[i], D_801F412C[i], D_801F412C[i]);
            setRGB2(back, D_801F412C[i + 1], D_801F412C[i + 1], D_801F412C[i + 1]);
            setRGB3(back, D_801F412C[i + 1], D_801F412C[i + 1], D_801F412C[i + 1]);
            {
                Coord x = {SELF(PartyMember)->pos.x.fixed};
                Coord y = {SELF(PartyMember)->pos.y.fixed};

                Area_CellAddPrim(x.fixed, y.fixed, (s8)D_801F4168[row], sizeof(POLY_GT4));
            }
        }

        /* Two sprites ride the rim of the copy, their size scaled by the camera depth. */
        for (i = 0; i < 2; i++) {
            angle                     = (row << 8) + (i << 7);
            g_ScratchPadVectors[2].vx = (u16)D_1F800034[0] + (rsin(angle) >> 8) * D_801F4150[8];
            g_ScratchPadVectors[2].vy = (u16)D_1F800034[1] + (rcos(angle) >> 8) * D_801F4150[8];
            g_ScratchPadVectors[2].vz = -(D_801F415C[8] << 5);
            RotTransPers(&g_ScratchPadVectors[2], (long*)&D_1F800034[6], &p, &flag);
            size = (abs(3 - ((g_FrameCount + row / 2) & 7)) + 0x10) * 0x1194;
            size = size / (g_AreaCameraOffsetZ + 0x1194) + (i << 3);
            quad = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyFT4(((POLY_FT4*)quad));
            SetShadeTex(((POLY_FT4*)quad), 0);
            setXY4(((POLY_FT4*)quad), (u16)D_1F800034[6] - size, (u16)D_1F800034[7] - size, (u16)D_1F800034[6] + size, (u16)D_1F800034[7] - size, (u16)D_1F800034[6] - size, (u16)D_1F800034[7] + size,
                   (u16)D_1F800034[6] + size, (u16)D_1F800034[7] + size);
            SetSemiTrans(((POLY_FT4*)quad), 1);
            setUV4(((POLY_FT4*)quad), 0xE0, 0x30, 0xFF, 0x30, 0xE0, 0x4F, 0xFF, 0x4F);
            ((POLY_FT4*)quad)->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0xAB : 0x3B;
            setRGB0(((POLY_FT4*)quad), tint, tint, tint / 2);
            ((POLY_FT4*)quad)->clut = getClut(160, 483);
            Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, (s8)(D_801F4168[row] + 1), sizeof(POLY_FT4));
        }
    }
}

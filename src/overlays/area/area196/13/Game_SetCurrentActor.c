#include "area196_13.h"

#ifdef NON_MATCHING
/* Draws the current actor's spinning cone: sixteen rotated copies of a tapered ring of twisted gouraud quads, each with a back quad, and two depth-scaled sprites per copy. */
NON_MATCHING void Game_SetCurrentActor(s32 tint) {
    POLY_GT4* quad;
    POLY_GT4* back;
    POLY_FT4* sprite;
    u16*      cell;
    s32       angle;
    s32       angle2;
    s32       row;
    s32       band;
    s32       side;
    s32       sprite_angle;
    s32       phase;
    s32       size;
    long      p;
    long      flag;

    /* The scratchpad screen pair: the actor's projected x and y at +0x00, the projected rim point at +0x0C. */
    cell    = (u16*)D_1F800034;
    angle   = 0;
    angle2  = 0x100;
    cell[0] = (TASK(PartyMember)->pos.x.fixed >> 9) - 0x4000;
    cell[1] = (TASK(PartyMember)->pos.y.fixed >> 9) - 0x4000;

    for (row = 0; row < 16; row++) {
        /* The payload rows one band walks: radii at +0x24/+0x25, twist scales at +0x30/+0x31, shade bytes from +0x00. */
        for (band = 7; band >= 0; band--) {
            quad = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyGT4(quad);
            SetSemiTrans(quad, 1);
            g_ScratchPadVectors[0].vx = cell[0] + (rsin(angle) >> 8) * D_801F412C[0x24 + band];
            g_ScratchPadVectors[0].vy = cell[1] + (rcos(angle) >> 8) * D_801F412C[0x24 + band];
            g_ScratchPadVectors[0].vz = -(D_801F412C[0x30 + band] << 5);
            g_ScratchPadVectors[1].vx = cell[0] + (rsin(angle2) >> 8) * D_801F412C[0x24 + band];
            g_ScratchPadVectors[1].vy = cell[1] + (rcos(angle2) >> 8) * D_801F412C[0x24 + band];
            g_ScratchPadVectors[1].vz = -(D_801F412C[0x30 + band] << 5);
            g_ScratchPadVectors[2].vx = cell[0] + (rsin(angle) >> 8) * D_801F412C[0x25 + band];
            g_ScratchPadVectors[2].vy = cell[1] + (rcos(angle) >> 8) * D_801F412C[0x25 + band];
            g_ScratchPadVectors[2].vz = -(D_801F412C[0x31 + band] << 5);
            g_ScratchPadVectors[3].vx = cell[0] + (rsin(angle2) >> 8) * D_801F412C[0x25 + band];
            g_ScratchPadVectors[3].vy = cell[1] + (rcos(angle2) >> 8) * D_801F412C[0x25 + band];
            g_ScratchPadVectors[3].vz = -(D_801F412C[0x31 + band] << 5);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&quad->x0, (long*)&quad->x1, (long*)&quad->x2, (long*)&quad->x3,
                          &p, &flag);
            setUVWH(quad, 0xB0, 0x20, 0x1F, 0x1F);
            quad->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0x325 : 0xD5;
            quad->clut  = getClut(0, 485);
            setRGB0(quad, D_801F412C[band], D_801F412C[band], D_801F412C[band]);
            setRGB1(quad, D_801F412C[band], D_801F412C[band], D_801F412C[band]);
            setRGB2(quad, D_801F412C[band + 1], D_801F412C[band + 1], D_801F412C[band + 1]);
            setRGB3(quad, D_801F412C[band + 1], D_801F412C[band + 1], D_801F412C[band + 1]);
            Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, (s8)D_801F412C[0x3C + row], sizeof(POLY_GT4));

            /* The back quad reuses the projected corners and texture with its own palette and blend mode. */
            back = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyGT4(back);
            SetShadeTex(back, 0);
            SetSemiTrans(back, 1);
            *(u32*)&back->x0 = *(u32*)&quad->x0;
            *(u32*)&back->x1 = *(u32*)&quad->x1;
            *(u32*)&back->x2 = *(u32*)&quad->x2;
            *(u32*)&back->x3 = *(u32*)&quad->x3;
            setUVWH(back, 0xB0, 0x20, 0x1F, 0x1F);
            back->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5;
            back->clut  = getClut(0, 484);
            setRGB0(back, D_801F412C[band], D_801F412C[band], D_801F412C[band]);
            setRGB1(back, D_801F412C[band], D_801F412C[band], D_801F412C[band]);
            setRGB2(back, D_801F412C[band + 1], D_801F412C[band + 1], D_801F412C[band + 1]);
            setRGB3(back, D_801F412C[band + 1], D_801F412C[band + 1], D_801F412C[band + 1]);
            Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, (s8)D_801F412C[0x3C + row], sizeof(POLY_GT4));
        }

        /* Two sprites ride the rim of the copy, their size scaled by the camera depth. */
        for (side = 0; side < 2; side++) {
            sprite_angle              = angle + (side << 7);
            g_ScratchPadVectors[2].vx = cell[0] + (rsin(sprite_angle) >> 8) * D_801F412C[0x2C];
            g_ScratchPadVectors[2].vy = cell[1] + (rcos(sprite_angle) >> 8) * D_801F412C[0x2C];
            g_ScratchPadVectors[2].vz = -(D_801F412C[0x38] << 5);
            RotTransPers(&g_ScratchPadVectors[2], (long*)&cell[6], &p, &flag);
            phase  = (g_FrameCount + row / 2) & 7;
            size   = abs(3 - phase) + 0x10;
            size   = size * 0x1194 / (g_AreaCameraOffsetZ + 0x1194) + (side << 3);
            sprite = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(sprite);
            SetShadeTex(sprite, 0);
            setXYWH(sprite, cell[6] - size, cell[7] - size, size * 2, size * 2);
            SetSemiTrans(sprite, 1);
            setUVWH(sprite, 0xE0, 0x30, 0x1F, 0x1F);
            sprite->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0xAB : 0x3B;
            setRGB0(sprite, tint, tint, tint / 2);
            sprite->clut = getClut(160, 483);
            Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, (s8)(D_801F412C[0x3C + row] + 1), sizeof(POLY_FT4));
        }

        angle += 0x100;
        angle2 += 0x100;
    }
}
#else
INCLUDE_ASM(Game_SetCurrentActor);
#endif

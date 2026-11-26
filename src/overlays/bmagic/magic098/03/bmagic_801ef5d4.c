#include "magic098_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Draws seventeen steps of four projected POLY_G4 bands like func_801EF5C4 of magic097 with wider band offsets: each
 * step 0x40 deeper than the last, the bands swaying with the effect ticker, their radius jittering by jitter_mask and
 * their height by up to three. */
MATCH void func_801EF5D4(s16 band_height, u16 radius, u16 jitter_mask) {
    POLY_G4* prim;
    long     p;
    long     flag;
    s32      tpage;
    s32      i;

    g_ScratchPad.cells.halves[0] = radius;
    g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->param.unk_0B & 0x1F) << 7;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->timer * 15;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->timer * 2;
    g_ScratchPad.cells.halves[6] = band_height - RANDOM_MASK(3);
    g_ScratchPadVectors[0].vy    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[1]), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[0].vz    = 0;
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    for (i = 1; i < 18; i++) {
        g_ScratchPad.cells.halves[1] = ((SELF(PartyMember)->param.unk_0B + i) & 0x1F) << 7;
        if RANDOM_MASK (1) {
            g_ScratchPad.cells.halves[0] = radius + (jitter_mask & rand());
        } else {
            g_ScratchPad.cells.halves[0] = radius - (jitter_mask & rand());
        }
        g_ScratchPad.cells.halves[5] = g_ScratchPad.cells.halves[6];
        g_ScratchPad.cells.halves[6] = band_height - RANDOM_MASK(3);
        g_ScratchPadVectors[2].vx    = 0;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz    = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx    = 0;
        g_ScratchPadVectors[3].vy    = g_ScratchPadVectors[0].vy - g_ScratchPad.cells.halves[5] * 2;
        g_ScratchPadVectors[3].vz    = g_ScratchPadVectors[0].vz;
        setVector(&g_ScratchPadVectors[0], 0, FIXED_MUL(rsin(g_ScratchPad.cells.halves[1]), g_ScratchPad.cells.halves[0]), -(i << 6));
        g_ScratchPadVectors[1].vx = 0;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vy - g_ScratchPad.cells.halves[6] * 2;
        g_ScratchPadVectors[1].vz = -(i << 6);
        prim                      = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        setRGB2(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy -= g_ScratchPad.cells.halves[6] * 2;
        g_ScratchPadVectors[1].vy -= g_ScratchPad.cells.halves[6];
        g_ScratchPadVectors[2].vy -= g_ScratchPad.cells.halves[5] * 2;
        g_ScratchPadVectors[3].vy -= g_ScratchPad.cells.halves[5];
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        setRGB3(prim, 1, 1, 1);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy += g_ScratchPad.cells.halves[6] * 4;
        g_ScratchPadVectors[1].vy += g_ScratchPad.cells.halves[6] * 3;
        g_ScratchPadVectors[2].vy += g_ScratchPad.cells.halves[5] * 4;
        g_ScratchPadVectors[3].vy += g_ScratchPad.cells.halves[5] * 3;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        setRGB1(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        setRGB3(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[0].vy += g_ScratchPad.cells.halves[6];
        g_ScratchPadVectors[1].vy += g_ScratchPad.cells.halves[6] * 2;
        g_ScratchPadVectors[2].vy += g_ScratchPad.cells.halves[5];
        g_ScratchPadVectors[3].vy += g_ScratchPad.cells.halves[5] * 2;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        g_ScratchPadVectors[0].vy -= g_ScratchPad.cells.halves[6] * 3;
    }
}

/* Draws the lightning bolt of the effect as LINE_G2 segments under one draw mode chosen by the graph type: the
 * longer-radius halfword copy of Effect_DrawBolt.h that sorts every segment into the cell of the effect position. */
MATCH void func_801EFE24(void) {
    LINE_G2* primitive;
    s16*     d;
    s16*     cell;
    s16*     vec;
    long     p;
    long     flag;
    u8       page;
    s32      tpage;
    s32      i;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    d                         = g_ScratchPadHalves;
    vec                       = g_ScratchPadVectorHalves;
    d[0]                      = 0x80;
    D_1F800002                = ((SELF(PartyMember)->param.unk_0B + 2) & 0xF) << 8;
    D_1F800008                = SELF(PartyMember)->timer;
    i                         = 1;
    D_1F800004                = RANDOM_MASK(0x3F);
    vec[0]                    = 0;
    g_ScratchPadVectors[0].vy = FIXED_MUL(rsin(D_1F800002), d[0]);
    g_ScratchPadVectors[0].vz = 0;
    if (i < D_1F800008) {
        cell = d + 1;
        do {
            primitive = (LINE_G2*)g_GfxPrimCursor;
            SetLineG2(primitive);
            SetSemiTrans(primitive, 1);
            RotTransPers(g_ScratchPadVectors, (long*)&primitive->x0, &p, &flag);
            if RANDOM_MASK (1) {
                g_ScratchPadHalves[0] = RANDOM_MASK(0x1F) + 0xA0;
            } else {
                g_ScratchPadHalves[0] = 0xA0 - RANDOM_MASK(0x1F);
            }
            page    = (SELF(PartyMember)->param.unk_0B + i + 2) & 0xF;
            vec[0]  = 0;
            cell[0] = page << 8;
            vec[1]  = FIXED_MUL(rsin(page << 8), cell[-1]);
            vec[2]  = -(i << 6);
            RotTransPers((SVECTOR*)vec, (long*)&primitive->x1, &p, &flag);
            setRGB0(primitive, cell[1], cell[1], 32);
            cell[1] = (rand() + 0x40) & 0x3F;
            setRGB1(primitive, cell[1], cell[1], 32);
            Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(LINE_G2));
            i++;
        } while (i < cell[3]);
    }
}

#include "overlays/bmagic/shared/BMagic_DrawFlickerRing.h"

MATCH void func_801F00C4(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    BMAGIC_DRAW_FLICKER_RING(15, 15, 12);
}

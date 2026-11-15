#include "magic098_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    BMagic_DispatchTaskPair(func_801EEC5C, func_801EEF38);
}

#include "overlays/bmagic/BMagic_SpawnAtTargets.h"

MATCH void func_801EEC5C(void) {
    u32          i;
    u32          slot;
    PartyMember* work;

    BMAGIC_SPAWN_AT_TARGETS(14);
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEF84 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFC8(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), g_Task->header.step);
    func_800AF764();
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF5D4(24, 32, 3);
        g_Task->param.unk_0B += 8;
        func_801EF5D4(16, 80, 0xF);
        g_Task->param.unk_0B += 2;
        func_801EFE24();
        g_Task->param.unk_0B += 6;
        func_801EF5D4(16, 128, 0x1F);
        g_Task->param.unk_0B -= 16;
        g_Task->unk_2E.half += 24;
        func_801F00C4();
        g_Task->unk_2E.half -= 48;
        func_801F00C4();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountDownAndPickRandom.h"

INCLUDE_ASM(func_801EF1B4);

/* func_801EF334 */
#include "overlays/bmagic/Effect_ReleaseTarget.h"

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

/* Draws seventeen steps of four projected POLY_G4 bands like func_801EF5C4 of magic097 with wider band offsets: each
 * step 0x40 deeper than the last, the bands swaying with the effect ticker, their radius jittering by jitter_mask and
 * their height by up to three. */
MATCH void func_801EF5D4(s16 band_height, u16 radius, u16 jitter_mask) {
    POLY_G4* prim;
    long     p;
    long     flag;
    s32      tpage;
    s32      i;

    D_1F800000.view.effect.params[0] = radius;
    D_1F800000.view.effect.params[1] = (g_Task->param.unk_0B & 0x1F) << 7;
    D_1F800000.view.effect.params[2] = g_Task->timer * 15;
    D_1F800000.view.effect.params[3] = g_Task->timer * 2;
    D_1F800000.view.effect.params[6] = band_height - RANDOM_MASK(3);
    D_1F800014[0].vy                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[1]), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vz                 = 0;
    tpage                            = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    for (i = 1; i < 18; i++) {
        D_1F800000.view.effect.params[1] = ((g_Task->param.unk_0B + i) & 0x1F) << 7;
        if RANDOM_MASK (1) {
            D_1F800000.view.effect.params[0] = radius + (jitter_mask & rand());
        } else {
            D_1F800000.view.effect.params[0] = radius - (jitter_mask & rand());
        }
        D_1F800000.view.effect.params[5] = D_1F800000.view.effect.params[6];
        D_1F800000.view.effect.params[6] = band_height - RANDOM_MASK(3);
        D_1F800014[2].vx                 = 0;
        D_1F800014[2].vy                 = D_1F800014[0].vy;
        D_1F800014[2].vz                 = D_1F800014[0].vz;
        D_1F800014[3].vx                 = 0;
        D_1F800014[3].vy                 = D_1F800014[0].vy - D_1F800000.view.effect.params[5] * 2;
        D_1F800014[3].vz                 = D_1F800014[0].vz;
        setVector(&D_1F800014[0], 0, FIXED_MUL(rsin(D_1F800000.view.effect.params[1]), D_1F800000.view.effect.params[0]), -(i << 6));
        D_1F800014[1].vx = 0;
        D_1F800014[1].vy = D_1F800014[0].vy - D_1F800000.view.effect.params[6] * 2;
        D_1F800014[1].vz = -(i << 6);
        prim             = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        setRGB2(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        D_1F800014[0].vy -= D_1F800000.view.effect.params[6] * 2;
        D_1F800014[1].vy -= D_1F800000.view.effect.params[6];
        D_1F800014[2].vy -= D_1F800000.view.effect.params[5] * 2;
        D_1F800014[3].vy -= D_1F800000.view.effect.params[5];
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        setRGB3(prim, 1, 1, 1);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        D_1F800014[0].vy += D_1F800000.view.effect.params[6] * 4;
        D_1F800014[1].vy += D_1F800000.view.effect.params[6] * 3;
        D_1F800014[2].vy += D_1F800000.view.effect.params[5] * 4;
        D_1F800014[3].vy += D_1F800000.view.effect.params[5] * 3;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        setRGB1(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        setRGB3(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        prim = (POLY_G4*)g_GfxPrimCursor;
        D_1F800014[0].vy += D_1F800000.view.effect.params[6];
        D_1F800014[1].vy += D_1F800000.view.effect.params[6] * 2;
        D_1F800014[2].vy += D_1F800000.view.effect.params[5];
        D_1F800014[3].vy += D_1F800000.view.effect.params[5] * 2;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[2]);
        if (i == 1) {
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        D_1F800014[0].vy -= D_1F800000.view.effect.params[6] * 3;
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

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    d          = D_1F800000_HALF;
    vec        = D_1F800014_HALF;
    d[0]       = 0x80;
    D_1F800002 = ((g_Task->param.unk_0B + 2) & 0xF) << 8;
    D_1F800008 = g_Task->timer;
    i          = 1;
    D_1F800004 = RANDOM_MASK(0x3F);
    vec[0]     = 0;
    D_1F800016 = FIXED_MUL(rsin(D_1F800002), d[0]);
    D_1F800018 = 0;
    if (i < D_1F800008) {
        cell = d + 1;
        do {
            primitive = (LINE_G2*)g_GfxPrimCursor;
            SetLineG2(primitive);
            SetSemiTrans(primitive, 1);
            RotTransPers(D_1F800014, (long*)&primitive->x0, &p, &flag);
            if RANDOM_MASK (1) {
                D_1F800000_HALF[0] = RANDOM_MASK(0x1F) + 0xA0;
            } else {
                D_1F800000_HALF[0] = 0xA0 - RANDOM_MASK(0x1F);
            }
            page    = (g_Task->param.unk_0B + i + 2) & 0xF;
            vec[0]  = 0;
            cell[0] = page << 8;
            vec[1]  = FIXED_MUL(rsin(page << 8), cell[-1]);
            vec[2]  = -(i << 6);
            RotTransPers((SVECTOR*)vec, (long*)&primitive->x1, &p, &flag);
            setRGB0(primitive, cell[1], cell[1], 32);
            cell[1] = (rand() + 0x40) & 0x3F;
            setRGB1(primitive, cell[1], cell[1], 32);
            Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(LINE_G2));
            i++;
        } while (i < cell[3]);
    }
}

#include "overlays/bmagic/BMagic_DrawFlickerRing.h"

MATCH void func_801F00C4(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    BMAGIC_DRAW_FLICKER_RING(15, 15, 12);
}

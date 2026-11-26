#include "magic107_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EED40);
}

/* The g_Task base for the span read must be fetched before the D_801EC364 store and the
 * z member read kept in place; both inline reads or an early span local shift the reload. */
MATCH void func_801EEC5C(void) {
    PartyMember* work;
    s32          scroll_x;
    u32          offset;

    Battle_CenterCamera();
    offset                                  = (Battle_AllocEffect(1, 25) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
    FIELD(PartyMember*, D_801EC3A4, offset) = TASK(PartyMember);
    FIELD(u8, D_801EC338, offset)           = g_BattleActiveActor->facing;
    scroll_x                                = g_AreaScrollTargetX;
    work                                    = TASK(PartyMember);
    FIELD(s32, D_801EC364, offset)          = scroll_x;
    FIELD(s32, D_801EC368, offset)          = g_AreaScrollTargetY;
    FIELD(s32, D_801EC36C, offset)          = work->pos.z.fixed + 0x04000000;
    SND_SEQueueSelection(0x100);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

MATCH void func_801EEDA0(void) {
    SYS_DISPATCH_BYTE(D_801F048C, TASK(PartyMember)->header.mode);
    if (TASK(PartyMember)->header.flags != 0) {
        func_801EEFD4();
        func_801EF0E4();
        func_801EF544();
        func_801EF290();
        PopMatrix();
        Effect_SetActorMatrixQuarterRoll();
        func_801F01AC();
        func_801EFAE0();
        func_801EFEA8();
        PopMatrix();
    }
}

MATCH void func_801EEE50(void) {
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.mode++;
}

MATCH void func_801EEEA0(void) {
    TASK(PartyMember)->unk_09 += 1;
    TASK(PartyMember)->timer += 1;
    if (TASK(PartyMember)->unk_09 == 0x20) {
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_AdvanceOnTick.h"

MATCH void func_801EEF5C(void) {
    PartyMember* active;

    TASK(PartyMember)->unk_09 = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->timer  = TASK(PartyMember)->timer - 1;
    if (TASK(PartyMember)->timer == 0) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = 255;
        Effect_Reset();
    }
}

MATCH void func_801EEFD4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    u8      angle;

    PushMatrix();
    if (TASK(PartyMember)->facing & 0x1) {
        rot.vx = 0;
        angle  = TASK(PartyMember)->unk_09 & 0x3F;
        rot.vy = (u32)rsin(angle << 6) >> 3;
        rot.vz = 0;
    } else {
        angle = TASK(PartyMember)->unk_09 & 0x3F;
        setVector(&rot, (u32)rsin(angle << 6) >> 3, 0, 0);
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
}

MATCH void func_801EF0E4(void) {
    LINE_G3* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32*     shade;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (LINE_G3*)g_GfxPrimCursor;
    SetLineG3(prim);
    SetSemiTrans(prim, 1);
    /* FAKE: retail stores the vx words through g_ScratchPadVectors and the vy/vz words through the scratchpad view, and the shade through a pointer local; the one-view spellings and the direct D_1F80000C store change the base register. */
    g_ScratchPad.vectors[0].vy = 0;
    g_ScratchPadVectors[0].vx  = 0;
    g_ScratchPad.vectors[0].vz = 0;
    g_ScratchPad.vectors[1].vy = 0;
    g_ScratchPadVectors[1].vx  = 0;
    g_ScratchPad.vectors[1].vz = 0x170;
    g_ScratchPad.vectors[2].vy = 0;
    g_ScratchPadVectors[2].vx  = 0;
    g_ScratchPad.vectors[2].vz = 384;
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    shade  = &D_1F80000C;
    *shade = TASK(PartyMember)->timer * 6;
    setRGB0(prim, *shade, *shade, *shade);
    setRGB1(prim, *shade, *shade, *shade);
    setRGB2(prim, 1, 1, 1);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(LINE_G3));
}

MATCH void func_801EF290(void) {
    POLY_F3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      semi;
    s32      tpage;

    semi  = TASK(PartyMember)->header.mode & 1;
    tpage = getTPage(TPAGE_DEPTH_4BIT, semi, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.words[0] = 32;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.words[0]), 448);
    for (i = 1; i <= 16; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[0].vz = 384;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[1].vz = g_ScratchPadVectors[2].vz;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.words[0]), FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.words[0]), 448);
        if (i < 8 || i > 12) {
            prim = (POLY_F3*)g_GfxPrimCursor;
            SetPolyF3(prim);
            SetSemiTrans(prim, semi);
            RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
            if (TASK(PartyMember)->header.mode & 1) {
                setRGB0(prim, TASK(PartyMember)->timer * 6, 1, 1);
            } else {
                if (i < 8) {
                    g_ScratchPad.cells.words[3] = 145 - i * 16;
                } else {
                    g_ScratchPad.cells.words[3] = (i - 8) * 16 + 17;
                }
                setRGB0(prim, 192, g_ScratchPad.cells.words[3], 16);
            }
            Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_F3));
        }
    }
}

MATCH void func_801EF544(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      row;
    s32      semi;
    s32      tpage;

    semi  = TASK(PartyMember)->header.mode & 1;
    tpage = getTPage(TPAGE_DEPTH_4BIT, semi, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.words[0] = 32;
    for (row = 8; row >= 5; row--) {
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos((row - 1) << 8), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos((row - 1) << 8), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[1].vz = FIXED_MUL(rsin((row - 1) << 8), g_ScratchPad.cells.words[0]) + 448;
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(0), FIXED_MUL(rcos(row << 8), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0), FIXED_MUL(rcos(row << 8), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[3].vz = FIXED_MUL(rsin(row << 8), g_ScratchPad.cells.words[0]) + 448;
        for (i = 1; i <= 16; i++) {
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz;
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(i << 8), FIXED_MUL(rcos((row - 1) << 8), g_ScratchPad.cells.words[0])),
                      FIXED_MUL(rcos(i << 8), FIXED_MUL(rcos((row - 1) << 8), g_ScratchPad.cells.words[0])), FIXED_MUL(rsin((row - 1) << 8), g_ScratchPad.cells.words[0]) + 448);
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;
            setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(i << 8), FIXED_MUL(rcos(row << 8), g_ScratchPad.cells.words[0])),
                      FIXED_MUL(rcos(i << 8), FIXED_MUL(rcos(row << 8), g_ScratchPad.cells.words[0])), FIXED_MUL(rsin(row << 8), g_ScratchPad.cells.words[0]) + 448);
            if (i >= 5) {
                prim = (POLY_F4*)g_GfxPrimCursor;
                SetPolyF4(prim);
                SetSemiTrans(prim, semi);
                RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2,
                              (long*)&prim->x3, &depth, &flag);
                if (TASK(PartyMember)->header.mode & 1) {
                    setRGB0(prim, TASK(PartyMember)->timer * 6, 1, 1);
                } else {
                    if (i < 8) {
                        g_ScratchPad.cells.words[3] = i * 16 + 1;
                    } else {
                        g_ScratchPad.cells.words[3] = 129 - (i - 8) * 16;
                    }
                    setRGB0(prim, 192, g_ScratchPad.cells.words[3], 1);
                }
                Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_F4));
            }
        }
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrixQuarterRoll.h"

MATCH void func_801EFAE0(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    u32      span;
    u32      angle_index;

    g_ScratchPad.cells.words[3] = (TASK(PartyMember)->timer >> 1) * 4 + 1;
    g_ScratchPad.cells.words[0] = 384;
    g_ScratchPad.cells.words[1] = 480;
    angle_index                 = TASK(PartyMember)->unk_09 & 0x3F;
    span                        = (TASK(PartyMember)->timer >> 1) + 1;
    g_ScratchPad.cells.words[2] = FIXED_MUL(rsin(angle_index << 6), 512) + 0x400;
    setVector(&g_ScratchPadVectors[1], 0, FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]));
    setVector(&g_ScratchPadVectors[3], 0, FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[1]), FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[1]));
    for (angle_index = (angle_index - 1) & 0x3F; angle_index != ((TASK(PartyMember)->unk_09 - span) & 0x3F); angle_index = (angle_index - 1) & 0x3F) {
        g_ScratchPad.cells.words[2] = FIXED_MUL(rsin(angle_index << 6), 512) + 0x400;
        g_ScratchPadVectors[0].vx   = 0;
        g_ScratchPadVectors[0].vy   = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz   = g_ScratchPadVectors[1].vz;
        setVector(&g_ScratchPadVectors[1], 0, FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]));
        g_ScratchPadVectors[2].vx = 0;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;
        setVector(&g_ScratchPadVectors[3], 0, FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[1]), FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[1]));
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.words[3], 1, 1);
        setRGB1(prim, g_ScratchPad.cells.words[3], 1, 1);
        setRGB2(prim, g_ScratchPad.cells.words[3] -= 4, 1, 1);
        setRGB3(prim, g_ScratchPad.cells.words[3], 1, 1);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EFEA8(void) {
    LINE_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    u32      count;
    u32      span;
    u32      angle_index;

    count                       = TASK(PartyMember)->timer >> 2;
    g_ScratchPad.cells.words[3] = count * 12 + 1;
    span                        = count + 1;
    for (angle_index = TASK(PartyMember)->unk_09 & 0x3F; angle_index != ((TASK(PartyMember)->unk_09 - span) & 0x3F); angle_index = (angle_index - 1) & 0x3F) {
        g_ScratchPad.cells.words[2] = FIXED_MUL(rsin(angle_index << 6), 512) + 0x400;
        g_ScratchPadVectors[0].vx   = 0;
        g_ScratchPadVectors[0].vy   = FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vz   = FIXED_MUL(rsin(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[1].vx   = 0;
        g_ScratchPadVectors[1].vy   = (u32)rcos(g_ScratchPad.cells.words[2]) >> 8;
        g_ScratchPadVectors[1].vz   = (u32)rsin(g_ScratchPad.cells.words[2]) >> 8;
        g_ScratchPadVectors[2].vx   = 0;
        g_ScratchPadVectors[2].vy   = (u32)(rcos(g_ScratchPad.cells.words[2]) * 21) >> 8;
        g_ScratchPadVectors[2].vz   = (u32)(rsin(g_ScratchPad.cells.words[2]) * 21) >> 8;
        g_ScratchPadVectors[3].vx   = 0;
        g_ScratchPadVectors[3].vy   = (u32)(rcos(g_ScratchPad.cells.words[2]) * 3) >> 5;
        g_ScratchPadVectors[3].vz   = (u32)(rsin(g_ScratchPad.cells.words[2]) * 3) >> 5;
        tpage                       = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (LINE_G4*)g_GfxPrimCursor;
        SetLineG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[3]);
        setRGB2(prim, g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[3]);
        setRGB3(prim, 1, 1, 1);
        g_ScratchPad.cells.words[3] -= 12;
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(LINE_G4));
    }
}

/* Draws the sixteen-segment fan of semi-transparent triangles around the effect, shaded by the timer. */
MATCH void func_801F01AC(void) {
    POLY_G3* prim;
    s32      y;
    s16      centre;
    s32      i;
    long     depth;
    long     flag;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.words[0] = 384;
    g_ScratchPad.cells.words[2] = ((rsin((TASK(PartyMember)->unk_09 & 0x3F) << 6) << 9) >> 12) + 0x400;
    y                           = FIXED_MUL(rcos(g_ScratchPad.cells.words[2]), g_ScratchPad.cells.words[0]);
    g_ScratchPad.cells.words[0] = 48;
    g_ScratchPadVectors[2].vx   = FIXED_MUL(rsin(0), g_ScratchPad.cells.words[0]);
    centre                      = y;
    y += FIXED_MUL(rcos(0), g_ScratchPad.cells.words[0]);
    g_ScratchPadVectors[2].vy = y;
    g_ScratchPadVectors[2].vz = 512;
    for (i = 1; i <= 16; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = centre;
        g_ScratchPadVectors[0].vz = 512;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[1].vz = 512;
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[2].vy = centre + FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[2].vz = 512;
        prim                      = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        g_ScratchPad.cells.words[3] = TASK(PartyMember)->timer * 3;
        setRGB0(prim, g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[3]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

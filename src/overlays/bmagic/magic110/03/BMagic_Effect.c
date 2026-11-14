#include "magic110_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    PartyMember* work;
    u32          slot;
    s32          i;
    u16*         src;
    u16*         dst;

    Battle_CenterCamera();
    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0x58;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 16) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_Task->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 16) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0x28;
    g_BattleEffects[slot].target.party = work;
    g_Task->param.unk_0B += 1;
    g_Task->param.unk_0B += 1;
    /* Copies arena palette rows 26 and 2 into the work copy with STP set, then restores the color 0 of each. */
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (i = 0; i < 256; i++) {
        dst[i] = src[i] | 0x8000;
    }
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    for (i = 0; i < 16; i++) {
        dst[i] = src[i] | 0x8000;
    }
    g_GfxPalettePending                                      = 1;
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EEE68(void) {
    if (g_Task->param.unk_0B == 2) {
        SND_QueueSelectionEffect(0x101);
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEDC(void) {
    u8 timer;
    u8 count;

    func_801EF148();
    if (g_FrameCount & 0x1) {
        timer = g_Task->timer;
        if (timer < 16U) {
            g_Task->timer = timer + 2;
        }
        count          = g_Task->unk_09 + 1;
        g_Task->unk_09 = count;
        if ((count & BYTE_MASK) == 0x10) {
            g_Task->header.mode += 1;
        }
    }
}

INCLUDE_ASM(func_801EEF80);

MATCH void func_801EF068(void) {
    u8 timer;
    u8 count;

    func_801EF148();
    if (!(g_FrameCount & 0x3)) {
        timer = g_Task->timer;
        if (timer != 0) {
            g_Task->timer = timer - 1;
        }
        count          = g_Task->unk_09 - 1;
        g_Task->unk_09 = count;
        if (!(count & BYTE_MASK)) {
            Battle_MarkDamaged(g_Battle.target_selector);
            g_Task->header.mode += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

/* Covers the screen with two semi-transparent quads in one flat shade of timer times 15;
 * the shade from byte 0x09 is stored first and overwritten. */
MATCH void func_801EF148(void) {
    POLY_G4* prim;
    s16*     shade;

    GFX_AddDitheredDrawMode(1, getTPage(0, 1, 320, 256));
    shade  = &D_1F800004;
    prim   = GFX_CURSOR(POLY_G4);
    *shade = g_Task->unk_09 * 15;
    *shade = g_Task->timer * 15;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0, 319, 120);
    setRGB0(prim, *shade, *shade, *shade);
    setRGB1(prim, *shade, *shade, *shade);
    setRGB2(prim, *shade, *shade, *shade);
    setRGB3(prim, *shade, *shade, *shade);
    GFX_AddPrim(1, sizeof(POLY_G4));
    prim = GFX_CURSOR(POLY_G4);
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0x78, 319, 239);
    setRGB0(prim, *shade, *shade, *shade);
    setRGB1(prim, *shade, *shade, *shade);
    setRGB2(prim, *shade, *shade, *shade);
    setRGB3(prim, *shade, *shade, *shade);
    GFX_AddPrim(1, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(1, getTPage(0, 0, 320, 256));
}

/* func_801EF3F8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF43C(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0478, g_Task->header.step);
    if ((g_Task->header.flags & 0x1) && g_Task->header.step >= 2) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

INCLUDE_ASM(func_801EF528);

MATCH void func_801EF648(void) {
    PartyMember* work;

    g_Task->unk_2E.half = (RANDOM_MASK(3)) + 0x9F;
    work                = g_Task;
    work->unk_30.half -= 2;
    work->scale.y += 0x2000;
    if (work->scale.y > 0x17FFF) {
        work->header.step++;
    }
}

MATCH void func_801EF6B4(void) {
    u16 position;

    g_Task->unk_2E.half = RANDOM_MASK(3) + 0x9F;
    position            = g_Task->unk_30.half - 4;
    g_Task->unk_30.half = position;
    if ((s16)position < 178) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF740(void) {
    u16 position;

    g_Task->unk_2E.half = RANDOM_MASK(3) + 0x9F;
    position            = g_Task->unk_30.half - 2;
    g_Task->unk_30.half = position;
    if ((s16)position < 128) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF7B4(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFA48();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF844);

MATCH void func_801EF8C0(void) {
    PartyMember* work;

    work = g_Task;
    if ((work->unk_14 += 0x40) == 0xC00) {
        work->header.step++;
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EFA48(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 2, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[2] = g_Task->unk_09 << 2;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;

    for (i = 1; i <= 64; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]));
        setRGB1(prim, LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]));
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]));
        GFX_AddPrim(2, sizeof(POLY_G3));
    }
}

#include "overlays/bmagic/BMagic_DarkRingQuads.h"

/* func_801EFC98 */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(2, getTPage(0, 2, 320, 256));
    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[1] = g_Task->unk_14 + 0x80;
    D_1F800000.view.effect.params[2] = g_Task->unk_09 * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(2, 2);
}

MATCH void func_801EFFB8(void) {
    SYS_DISPATCH_BYTE(D_801F049C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F0138();
        func_801F01E8();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801F0040);

MATCH void func_801F00D8(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 + 2;
    work         = g_Task;
    work->timer  = work->timer - 1;
    if (work->timer == 0) {
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix2(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

MATCH void func_801F01E8(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 3;
    D_1F800000.view.effect.params[2] = g_Task->timer * 2;
    D_1F800014[0].vx                 = FIXED_MUL(rcos(ANGLE_45), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vy                 = FIXED_MUL(rsin(ANGLE_45), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vz                 = 0;
    D_1F800014[1].vx                 = FIXED_MUL(rcos(1536), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rsin(1536), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vz                 = 0;
    D_1F800014[2].vx                 = FIXED_MUL(rcos(3584), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rsin(3584), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[3].vx                 = FIXED_MUL(rcos(2560), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vy                 = FIXED_MUL(rsin(2560), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vz                 = 0;
    setTPage(prim, 0, 1, 832, 256);
    /* FAKE: a volatile store keeps the clut write ahead of the texture-point stores; the plain setClut sinks it below them. */
    *FAKE_VOLATILE_PTR(u16, &prim->clut) = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]), LOHU(D_1F800000.view.effect.params[2]));
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    GFX_AddPrim(3, sizeof(POLY_FT4));
}

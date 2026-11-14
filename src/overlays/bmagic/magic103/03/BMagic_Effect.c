#include "magic103_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    u32  slot;
    u32  i;
    u16* dst;
    u16* src;

    slot                               = Battle_AllocEffect(1, 45) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 2;
    g_Task->param.unk_0B               = 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, 45) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_Task->param.unk_0B += 1;
    }
    slot                               = Battle_AllocEffect(1, 45) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_Task->param.unk_0B += 1;
    /* Copies the first two colour rows of arena palette 26 into the work copy with STP set, then clears colour 0 of each. */
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (i = 1; i < 16; i++) {
        dst[i]      = src[i] | 0x8000;
        dst[i + 16] = src[i + 16] | 0x8000;
    }
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[0]  = 0;
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[16] = 0;
    g_GfxPalettePending                                         = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_Hit.h"

#include "shared/Effect_StartPlaying.h"

/* func_801EEEC8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF0C(void) {
    SYS_DISPATCH_BYTE(D_801F07A0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF1D8();
        PopMatrix();
    }
}

MATCH void func_801EEF94(void) {
    PartyMember* src;

    src                      = g_Battle.selected_actor;
    g_Task->pos.x.fixed      = src->pos.x.fixed;
    g_Task->pos.y.fixed      = src->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(src->pos.z);
    g_Task->unk_09           = 0;
    g_Task->timer            = 0;
    g_Task->header.step      = g_Task->header.step + 1;
}

MATCH void func_801EEFF4(void) {
    u8 counter;

    if (g_Task->unk_09 == 4) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    SP_REF(s16, 0) = g_Task->unk_09 * 0x1C;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x8) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF094(void) {
    u8 count;

    SP_REF(s16, 0u) = (g_Task->unk_09 * 4) + 0xC0;
    g_Task->timer += 1;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* Draws an eight-band textured dome: band 24 down to 17 is a ring of 32 semi-transparent GT4 quads between the
 * radii and heights that rcos and rsin of the band give for the scratch radius word 0, each quad placed in its area
 * cell; v scrolls with timer and the shades fade in by row as unk_09 grows. */
MATCH void func_801EF1D8(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       tpage;
    s32       band;
    s32       row;
    s32       i;
    s32       x;
    s32       y;

    for (band = 24, row = 1; band >= 17; band--, row++) {
        D_1F800000.view.effect.params[3] = 0x81;
        D_1F800000.view.effect.params[4] = 0x81;
        if (row - 1 < g_Task->unk_09 - 16) {
            D_1F800000.view.effect.params[3] = g_Task->unk_09 - 15 - row;
            if (D_1F800000.view.effect.params[3] < 17) {
                D_1F800000.view.effect.params[3] = 0x81 - D_1F800000.view.effect.params[3] * 8;
            } else {
                D_1F800000.view.effect.params[3] = 1;
            }
        }
        if (row < g_Task->unk_09 - 16) {
            D_1F800000.view.effect.params[4] = g_Task->unk_09 - 16 - row;
            if (D_1F800000.view.effect.params[4] < 17) {
                D_1F800000.view.effect.params[4] = 0x81 - D_1F800000.view.effect.params[4] * 8;
            } else {
                D_1F800000.view.effect.params[4] = 1;
            }
        }
        D_1F800000.view.effect.params[1] = FIXED_MUL(rcos((band - 1) << 7), D_1F800000.view.effect.params[0]);
        D_1F800000.view.effect.params[2] = FIXED_MUL(rcos(band << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
        D_1F800014[1].vz = D_1F800014[0].vz = FIXED_MUL(rsin((band - 1) << 7), D_1F800000.view.effect.params[0]);
        D_1F800014[3].vx                    = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[2]);
        D_1F800014[3].vy                    = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[2]);
        D_1F800014[3].vz = D_1F800014[2].vz = FIXED_MUL(rsin(band << 7), D_1F800000.view.effect.params[0]);
        for (i = 1; i <= 32; i++) {
            D_1F800014[0].vx = D_1F800014[1].vx;
            D_1F800014[0].vy = D_1F800014[1].vy;
            D_1F800014[1].vx = FIXED_MUL(rsin(i << 7), D_1F800000.view.effect.params[1]);
            D_1F800014[1].vy = FIXED_MUL(rcos(i << 7), D_1F800000.view.effect.params[1]);
            D_1F800014[2].vx = D_1F800014[3].vx;
            D_1F800014[2].vy = D_1F800014[3].vy;
            D_1F800014[3].vx = FIXED_MUL(rsin(i << 7), D_1F800000.view.effect.params[2]);
            D_1F800014[3].vy = FIXED_MUL(rcos(i << 7), D_1F800000.view.effect.params[2]);
            x                = (D_1F800014[3].vx << 9) + g_Task->pos.x.fixed;
            y                = (D_1F800014[3].vy << 9) + g_Task->pos.y.fixed;
            if (GetGraphType() == 1 || GetGraphType() == 2) {
                tpage = 0xA5;
            } else {
                tpage = 0x35;
            }
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 2, sizeof(DR_MODE));
            prim = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyGT4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
            prim->tpage = GetTPage(0, 1, 0x340, 0x100);
            prim->clut  = GetClut(0, 0x1FA);
            prim->u0    = i * 8;
            prim->v0    = (band - 16) * 8 + 32 + g_Task->timer * 4;
            prim->u1    = i * 8 + 8;
            prim->v1    = (band - 16) * 8 + 32 + g_Task->timer * 4;
            prim->u2    = i * 8;
            prim->v2    = g_Task->timer * 4 + (band - 16) * 8 + 0x28;
            prim->u3    = i * 8 + 8;
            prim->v3    = g_Task->timer * 4 + (band - 16) * 8 + 0x28;
            setRGB0(prim, LOHU(D_1F800000.view.effect.params[4]), LOHU(D_1F800000.view.effect.params[4]), LOHU(D_1F800000.view.effect.params[4]));
            setRGB1(prim, LOHU(D_1F800000.view.effect.params[4]), LOHU(D_1F800000.view.effect.params[4]), LOHU(D_1F800000.view.effect.params[4]));
            setRGB2(prim, LOHU(D_1F800000.view.effect.params[3]), LOHU(D_1F800000.view.effect.params[3]), LOHU(D_1F800000.view.effect.params[3]));
            setRGB3(prim, LOHU(D_1F800000.view.effect.params[3]), LOHU(D_1F800000.view.effect.params[3]), LOHU(D_1F800000.view.effect.params[3]));
            Area_AddCellPrim(x, y, 2, sizeof(POLY_GT4));
        }
    }
}

/* Draw the magic103 shaded ring band. Retail writes both radii to params[0], so the inner
 * edge uses whatever params[1] holds. */
MATCH void func_801EF7CC(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      scale;

    scale                            = rcos(0x800) * 6;
    D_1F800000.view.effect.params[0] = FIXED_MUL(scale, g_Task->unk_09 + 0xE1);
    scale                            = rcos(0x800) * 6;
    D_1F800000.view.effect.params[0] = FIXED_MUL(scale, g_Task->unk_09 + 0xE0);
    D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));

    for (i = 1; i <= 32; i++) {
        prim                             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx                 = D_1F800014[1].vx;
        D_1F800014[0].vy                 = D_1F800014[1].vy;
        D_1F800014[0].vz                 = 0;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = 0;
        D_1F800014[2].vx                 = D_1F800014[3].vx;
        D_1F800014[2].vy                 = D_1F800014[3].vy;
        D_1F800014[2].vz                 = 0;
        D_1F800014[3].vx                 = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vy                 = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vz                 = 0;
        D_1F800000.view.effect.params[3] = 0x29 - g_Task->unk_09;
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
}

MATCH void func_801EFB10(void) {
    SYS_DISPATCH_BYTE(D_801F07C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EFE20();
    }
}

MATCH void func_801EFB88(void) {
    PartyMember* work;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        work              = g_Task;
        work->pos.x.fixed = g_BattleSelectedActor->pos.x.fixed + D_801F07AC[work->param.unk_0B].x;
        work->pos.y.fixed = g_BattleSelectedActor->pos.y.fixed + D_801F07AC[work->param.unk_0B].y;
        work->pos.z.fixed = g_BattleSelectedActor->pos.z.fixed + D_801F07AC[work->param.unk_0B].z;
        work->unk_09      = 0;
        g_Task->timer     = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFC70(void) {
    u8 count;

    Battle_ProjectRange();
    g_Task->timer += 2;
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 8) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFCF4(void) {
    PartyMember* work;
    u8           counter;
    s32          drop;

    Battle_ProjectRange();
    work         = g_Task;
    counter      = work->unk_09 + 1;
    drop         = (VOL(u8, work->unk_09) - 8) / 2;
    work->unk_09 = counter;
    work->unk_30.half -= drop;
    if ((counter & BYTE_MASK) == 0x1C) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD74(void) {
    u8 counter;

    Battle_ProjectRange();
    g_Task->unk_30.half -= (g_Task->unk_09 - 8) / 2;
    if ((g_Task->unk_09 & BYTE_MASK) != 0x2C) {
        g_Task->unk_09 = g_Task->unk_09 + 1;
    }
    counter       = g_Task->timer - 1;
    g_Task->timer = counter;
    if (!(counter & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

/* Draw the magic103 tinted glow quad, turning with the effect timer (byte 0x09) around the
 * effect screen point. */
MATCH void func_801EFE20(void) {
    POLY_GT4* prim;
    s32       tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    if (g_Task->header.step >= 2) {
        D_1F800000.view.effect.params[0] = g_Task->unk_09 * 2;
    } else {
        D_1F800000.view.effect.params[0] = (g_Task->unk_09 - 8) / 4 + 0x10;
    }
    D_1F800000.view.effect.params[3] = g_Task->timer * 8;
    D_1F800000.view.effect.params[4] = g_Task->timer * 7;
    D_1F800000.view.effect.params[5] = g_Task->timer * 4;
    D_1F800000.view.effect.params[6] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[7] = g_Task->unk_30.half;
    prim->x0                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin((u8)(g_Task->unk_09 + 0x80) << 4), D_1F800000.view.effect.params[0]);
    prim->y0                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos((u8)(g_Task->unk_09 + 0x80) << 4), D_1F800000.view.effect.params[0]);
    prim->x1                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin((u8)(g_Task->unk_09 + 0x40) << 4), D_1F800000.view.effect.params[0]);
    prim->y1                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos((u8)(g_Task->unk_09 + 0x40) << 4), D_1F800000.view.effect.params[0]);
    prim->x2                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin((u8)(g_Task->unk_09 + 0xC0) << 4), D_1F800000.view.effect.params[0]);
    prim->y2                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos((u8)(g_Task->unk_09 + 0xC0) << 4), D_1F800000.view.effect.params[0]);
    prim->x3                         = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(g_Task->unk_09 << 4), D_1F800000.view.effect.params[0]);
    prim->y3                         = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(g_Task->unk_09 << 4), D_1F800000.view.effect.params[0]);
    prim->tpage                      = GetTPage(0, 1, 832, 256);
    prim->clut                       = GetClut(16, 506);
    prim->u0                         = 1;
    prim->v0                         = 1;
    prim->u1                         = 31;
    prim->v1                         = 1;
    prim->u2                         = 1;
    prim->v2                         = 31;
    prim->u3                         = 31;
    prim->v3                         = 31;
    setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
    setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
    setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
    setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5]);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_GT4));
}

MATCH void func_801F02BC(void) {
    SYS_DISPATCH_BYTE(D_801F07D4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F04E0();
        PopMatrix();
    }
}

MATCH void func_801F0344(void) {
    PartyMember* src;

    src                 = g_Battle.selected_actor;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->timer       = 0;
    g_Task->header.step = g_Task->header.step + 1;
}

MATCH void func_801F03A4(void) {
    PartyMember* work;

    work = g_Task;
    work->timer += 2;
    work = g_Task;
    work->unk_09++;
    if (work->unk_09 == 8) {
        work = g_Task;
        work->header.step++;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStepAt30.h"

#include "overlays/bmagic/Effect_CountDownTimerCapped.h"

MATCH void func_801F04E0(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      scale;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    if (g_Task->header.step >= 2) {
        D_1F800000.view.effect.params[0] = FIXED_MUL(g_Task->unk_09 * 4 + 0x160, rcos(0x800));
    } else {
        scale                            = rcos(0x800) * 48;
        D_1F800000.view.effect.params[0] = FIXED_MUL(scale, g_Task->unk_09);
    }
    D_1F800000.view.effect.params[3] = g_Task->timer << 3;
    D_1F800000.view.effect.params[4] = g_Task->timer * 6;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;

    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
}

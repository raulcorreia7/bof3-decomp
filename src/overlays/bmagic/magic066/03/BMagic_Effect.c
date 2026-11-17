#include "magic066_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* task;
    PartyMember* battler;
    u32          slot;
    u32          i;
    u16*         src;
    u16*         dst;

    battler                            = g_BattleEffectBattler;
    task                               = g_Task;
    task->pos.x.fixed                  = battler->pos.x.fixed;
    task->pos.y.fixed                  = battler->pos.y.fixed;
    task->pos.z.fixed                  = battler->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 17) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    /* Copies arena palette rows 26 and 2 into the work copy with STP set, then restores row 2's color 0. */
    for (i = 0, dst = MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW)), src = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW)); i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    {
        u16* row_dst;
        u16* row_src;

        for (i = 0, row_dst = MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BMAGIC_ROW)), row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00); i < 16; i++) {
            *row_dst++ = *row_src++ | PSX_COLOR_STP_BIT;
        }
    }
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BMAGIC_ROW)) = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                             = 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 24;
    g_Task->header.mode += 1;
}

MATCH void func_801EEDB8(void) {
    u8           timer;
    u32          slot;
    PartyMember* work;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        slot                               = Battle_AllocEffect(1, 17) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x20);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

/* func_801EEEBC */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF00(void) {
    SYS_DISPATCH_BYTE(D_801F006C, g_Task->header.step);
    if (BATTLE_ACTIVE_WORK->param.unk_0B != 0xFF) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801EF158);
    }
}

MATCH void func_801EEF78(void) {
    g_Task->pos.x.fixed  = g_AreaScrollTargetX + 0xFFEE0000;
    g_Task->pos.y.fixed  = g_AreaScrollTargetY + 0x880000;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->param.unk_0B = 0x1A;
    g_Task->unk_09       = 0x10;
    g_Task->unk_10       = 0;
    g_Task->unk_14       = 0xF0;
    g_Task->header.step++;
}

MATCH void func_801EEFF8(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->pos.y.fixed += 0xFFFF4000;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF04C(void) {
    s32 phase;

    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x1F;
    phase                = g_Task->unk_10 + 2;
    g_Task->unk_10       = phase;
    if (phase == 0x80) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0A4(void) {
    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x1F;
    g_Task->unk_14 -= 2;
    g_Task->unk_10 -= 2;
    if (g_Task->unk_10 == 0x20) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF108(void) {
    s32 count;

    count = g_Task->unk_10 - 1;
    g_Task->unk_14 -= 2;
    g_Task->unk_10 = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

MATCH void func_801EF158(void) {
    POLY_FT4* poly;
    POLY_G4*  prim;
    long      depth;
    long      flag;
    s32       tpage;
    s32       i;
    s16       angle;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, tpage);
    g_ScratchPad.cells.halves[0] = g_Task->unk_14;
    angle                        = g_Task->param.unk_0B;
    g_ScratchPadVectors[0].vx    = 0;
    g_ScratchPadVectors[0].vy    = 0;
    angle &= 0x1F;
    g_ScratchPad.cells.halves[3] = angle << 7;
    g_ScratchPadVectors[0].vz    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
    for (i = 1; i < 128; i++) {
        poly = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(poly);
        PSX_SET_SEMI_TRANSPARENT(poly);
        g_ScratchPadVectors[2].vx    = 0;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz    = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx    = 0x1000;
        g_ScratchPadVectors[3].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[3].vz    = g_ScratchPadVectors[0].vz;
        angle                        = (g_Task->param.unk_0B + i) & 0x1F;
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPad.cells.halves[3] = angle << 7;
        g_ScratchPadVectors[0].vy    = -(i * 128 + (g_Task->unk_10 >> 1) * i);
        g_ScratchPadVectors[0].vz    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vx    = 0x1000;
        g_ScratchPadVectors[1].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[1].vz    = g_ScratchPadVectors[0].vz;
        if (g_Task->header.step == 4) {
            g_ScratchPad.cells.halves[1] = (g_Task->unk_10 / 2) * 8;
        } else {
            g_ScratchPad.cells.halves[1] = 0x80;
        }
        setRGB0(poly, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        poly->tpage                  = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 0x340, 0x100);
        poly->clut                   = GetClut(0, 0x1FA);
        g_ScratchPad.cells.halves[4] = 0xE0 - (((g_Task->param.unk_0B + i) & 7) << 4);
        setUV4(poly, 0, g_ScratchPad.cells.halves[4], 0xF8, g_ScratchPad.cells.halves[4], 0, g_ScratchPad.cells.halves[4] + 0x10, 0xF8, g_ScratchPad.cells.halves[4] + 0x10);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
    }
    i -= 2;
    angle                        = (g_Task->param.unk_0B + i) & 0x1F;
    g_ScratchPadVectors[0].vx    = 0;
    g_ScratchPad.cells.halves[3] = angle << 7;
    g_ScratchPadVectors[0].vy    = -(i * 128 + (g_Task->unk_10 >> 1) * i);
    g_ScratchPadVectors[0].vz    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
    for (i++; i < 129; i++) {
        prim                         = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[2].vx    = 0;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz    = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx    = 0x1000;
        g_ScratchPadVectors[3].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[3].vz    = g_ScratchPadVectors[0].vz;
        angle                        = (g_Task->param.unk_0B + i) & 0x1F;
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPad.cells.halves[3] = angle << 7;
        g_ScratchPadVectors[0].vy    = -(i * 128 + (g_Task->unk_10 >> 1) * i);
        g_ScratchPadVectors[0].vz    = FIXED_MUL(rsin(angle << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vx    = 0x1000;
        g_ScratchPadVectors[1].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[1].vz    = g_ScratchPadVectors[0].vz;
        if (g_Task->header.step == 4) {
            g_ScratchPad.cells.halves[1] = (g_Task->unk_10 / 2) * 12;
        } else {
            g_ScratchPad.cells.halves[1] = 0xC0;
        }
        if (i == 128) {
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
            setRGB3(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        } else {
            setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
            setRGB1(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
            setRGB2(prim, 1, 1, 1);
            setRGB3(prim, 1, 1, 1);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, tpage);
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF834(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
}

MATCH void func_801EF878(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        D_801F00B0[i] = 0;
    }
    g_Task->unk_09 = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF8C8(void) {
    u8 timer;

    func_801EF984();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 96) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF930(void) {
    u8 timer;

    func_801EF984();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if ((timer & BYTE_MASK) == 128) {
        Effect_Reset();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF984(void) {
}
#else
INCLUDE_ASM(func_801EF984);
#endif

MATCH void func_801EFCC8(void) {
    POLY_FT4* poly;
    long      depth;
    long      flag;
    s32       i;

    for (i = 0; i < 4; i++) {
        if (i * 3 < g_Task->unk_09 && D_801F00B0[i] < 16) {
            poly = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(poly);
            PSX_SET_SEMI_TRANSPARENT(poly);
            g_ScratchPad.cells.halves[0] = D_801F00B0[i] * 4 + 50;
            g_ScratchPad.cells.halves[2] = D_801F00B0[i] * 15;
            g_ScratchPadVectors[0].vx    = (rcos(0x200) * g_ScratchPad.cells.halves[0]) >> 12;
            g_ScratchPadVectors[0].vy    = (rsin(0x200) * g_ScratchPad.cells.halves[0]) >> 12;
            g_ScratchPadVectors[0].vz    = -g_ScratchPad.cells.halves[2];
            setVector(&g_ScratchPadVectors[1], (rcos(0x600) * g_ScratchPad.cells.halves[0]) >> 12, (rsin(0x600) * g_ScratchPad.cells.halves[0]) >> 12, -g_ScratchPad.cells.halves[2]);
            setVector(&g_ScratchPadVectors[2], (rcos(0xE00) * g_ScratchPad.cells.halves[0]) >> 12, (rsin(0xE00) * g_ScratchPad.cells.halves[0]) >> 12, -g_ScratchPad.cells.halves[2]);
            setVector(&g_ScratchPadVectors[3], (rcos(0xA00) * g_ScratchPad.cells.halves[0]) >> 12, (rsin(0xA00) * g_ScratchPad.cells.halves[0]) >> 12, -g_ScratchPad.cells.halves[2]);
            poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x340, 0x100);
            poly->clut  = GetClut(0, 0x1E2);
            setUVWH(poly, 0, 0, 32, 32);
            g_ScratchPad.cells.halves[1] = 0x41 - (D_801F00B0[i] >> 1) * 4;
            setRGB0(poly, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3,
                          &depth, &flag);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_FT4));
        }
    }
}

MATCH void func_801EFFB0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 3072, 0, 0);
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

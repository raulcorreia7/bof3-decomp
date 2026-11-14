#include "magic222_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    u32  slot;
    s32  i;
    u16* dst;
    u16* src;

    Battle_CenterCamera();
    Battle_ProjectRange();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 96) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].arg.unk_09   = 16;
    g_Task->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 96) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 16;
    g_Task->param.unk_0B += 1;
    /* Copies arena palette rows 26 and 2 into the work copy with STP set, then restores the first color of each. */
    for (i = 0, dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW), src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW); i < 256; i++) {
        *dst++ = *src++ | 0x8000;
    }
    {
        u16* row_dst;
        u16* row_src;

        for (i = 0, row_dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW), row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00); i < 16; i++) {
            *row_dst++ = *row_src++ | 0x8000;
        }
    }
    g_GfxPalettePending                                      = 1;
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
}

#include "overlays/bmagic/Effect_CountDownTimerQueueEffect.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEE0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF24(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0D64, g_Task->header.step);
    if ((g_Task->header.flags & 0x1) && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EEFC8);

/* Lets the effect fall onto the battler's height and, at its timer's end, starts eight effect slots, lifts the
 * camera pitch and moves to the next step. */
MATCH void func_801EF148(void) {
    u32 slot;
    u8  i;

    g_Task->unk_14 -= g_Task->unk_20;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + g_Task->unk_14;
    if (--g_Task->unk_09 == 0) {
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 1));
        for (i = 0; i < 8; i++) {
            slot                               = Battle_AllocEffect(1, 0x60) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            g_BattleEffects[slot].header.mode  = 2;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
        g_AreaCameraAngle.vx += 20;
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

/* func_801EF274 */
MATCH void Effect_SwingCameraAngle(void) {
    BMAGIC_SWING_CAMERA(22);
}

MATCH void func_801EF324(void) {
    u8           count;
    u32          slot;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        slot                               = Battle_AllocEffect(1, 96) & BYTE_MASK;
        work                               = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 3;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffectBattler->param.unk_0B += 1;
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = 0x40;
        g_Task->unk_5E = 0x40;
        g_Task->unk_5F = 0x40;
        g_Task->unk_09 = 12;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_StartTint.h"

MATCH void func_801EF4F0(void) {
    g_Task->unk_5D -= 0x10;
    g_Task->unk_5E -= 0x10;
    g_Task->unk_5F -= 0x10;
    g_Task->scale.x += 0x1800;
    if ((s8)g_Task->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF5A4(void) {
    SYS_DISPATCH_BYTE(D_801F0D7C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF87C();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
}

MATCH void func_801EF634(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        src              = g_BattleEffectBattler;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        dst->pos.z       = src->pos.z;
        dst->unk_14      = 0;
        dst->unk_09      = 0;
        g_Task->timer    = 38;
        g_Task->header.step++;
    }
}

MATCH void func_801EF6C8(void) {
    g_Task->unk_09 += 1;
    g_Task->unk_14 += 6;
    if (g_Task->unk_09 == 0x10) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF87C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 2, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[5] = g_Task->unk_09 << 2;
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
        setRGB0(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB1(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
}

#include "overlays/bmagic/BMagic_DarkRingQuads.h"

/* func_801EFACC */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(5, getTPage(0, 2, 320, 256));
    D_1F800000.view.effect.params[0] = g_Task->unk_14;
    D_1F800000.view.effect.params[1] = g_Task->unk_14 * 2;
    D_1F800000.view.effect.params[5] = g_Task->unk_09 * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(5, 5);
}

MATCH void func_801EFDEC(void) {
    SYS_DISPATCH_BYTE(D_801F0D8C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F0168();
        func_801F0218();
        PopMatrix();
    }
}

MATCH void func_801EFE74(void) {
    s32  r;
    s32  phase;
    s16* angle = &D_1F800004;

    r                   = rand();
    phase               = g_Task->param.unk_0B;
    g_Task->unk_0C      = (r & 0x7) + 8;
    *angle              = phase << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(*angle) * g_Task->unk_0C);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(*angle) * g_Task->unk_0C);
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_Task->unk_09      = 8;
    g_Task->timer       = 16;
    g_Task->header.step += 1;
}

MATCH void func_801EFF7C(void) {
    PartyMember* task;
    s16*         angle_cell;
    s32          direction;
    s32          velocity;

    task       = g_Task;
    angle_cell = &D_1F800004;
    direction  = task->param.unk_0B;
    task->unk_0C += 1;
    *angle_cell         = direction << 9;
    velocity            = rsin((s16)(direction << 9)) * g_Task->unk_0C;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + velocity;
    velocity            = rcos(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + velocity;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0070(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(phase << 9)) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    count               = g_Task->timer - 1;
    g_Task->timer       = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix3(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

MATCH void func_801F0218(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[0] = 0x100;
    D_1F80000A                       = g_Task->timer << 3;
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
    /* FAKE: a volatile store keeps the clut write ahead of the texture-point stores; the best pure-C body is 0x2C8 against retail's 0x2D4. */
    *FAKE_VOLATILE_PTR(u16, &prim->clut) = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, D_1F80000A, D_1F80000A, D_1F80000A);
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

MATCH void func_801F0504(void) {
    SYS_DISPATCH_BYTE(D_801F0D98, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F07A8();
        func_801F07A8();
    }
}

INCLUDE_ASM(func_801F0584);

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801F066C(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 16;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F06C8(void) {
    PartyMember* work;

    work = g_Task;
    work->param.unk_0B += 4;
    work = g_Task;
    work->timer--;
    if (work->timer == 0) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F0730(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->param.unk_0B += 4;
    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}

/* Draws 32 columns, 16 wide, from 0x100 left of the effect position: per column two semi-transparent Gouraud quads
 * above the row and two mirrored below, their heights following rsin over the column with radii unk_0B and twice
 * unk_0B, shaded by unk_09. */
MATCH void func_801F07A8(void) {
    POLY_G4*     prim;
    PartyMember* work;
    s32          tpage;
    s32          i;
    s16          x;
    s16          y;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    work                             = g_Task;
    D_1F800000.view.effect.params[0] = work->param.unk_0B;
    D_1F800000.view.effect.params[1] = work->param.unk_0B * 2;
    D_1F800000.view.effect.params[5] = work->unk_09 * 15;
    D_1F800000.view.effect.params[6] = work->unk_09 * 8;
    D_1F800000.view.effect.params[7] = work->unk_09 * 8;
    x                                = work->unk_2E.half - 0x100;
    y                                = work->unk_30.half;
    for (i = 0; (u32)(i & BYTE_MASK) < 32; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y + FIXED_MUL(rsin((i & BYTE_MASK) << 6), D_1F800000.view.effect.params[0]));
        prim->x2 = x;
        prim->y2 = y;
        prim->x1 = x + 16;
        prim->y1 = y + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), D_1F800000.view.effect.params[0]);
        prim->x3 = x + 16;
        prim->y3 = y;
        setRGB0(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        setRGB1(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB3(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        GFX_AddPrim(2, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y + FIXED_MUL(rsin((i & BYTE_MASK) << 6), D_1F800000.view.effect.params[1]));
        prim->x2 = x;
        prim->y2 = y + FIXED_MUL(rsin((i & BYTE_MASK) << 6), D_1F800000.view.effect.params[0]);
        prim->x1 = x + 16;
        prim->y1 = y + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), D_1F800000.view.effect.params[1]);
        prim->x3 = x + 16;
        prim->y3 = y + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), D_1F800000.view.effect.params[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        setRGB3(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        GFX_AddPrim(2, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y - FIXED_MUL(rsin((i & BYTE_MASK) << 6), D_1F800000.view.effect.params[0]));
        prim->x2 = x;
        prim->y2 = y;
        prim->x1 = x + 16;
        prim->y1 = y - FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), D_1F800000.view.effect.params[0]);
        prim->x3 = x + 16;
        prim->y3 = y;
        setRGB0(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        setRGB1(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB3(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        GFX_AddPrim(2, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y - FIXED_MUL(rsin((i & BYTE_MASK) << 6), D_1F800000.view.effect.params[1]));
        prim->x2 = x;
        prim->y2 = y - FIXED_MUL(rsin((i & BYTE_MASK) << 6), D_1F800000.view.effect.params[0]);
        prim->x1 = x + 16;
        prim->y1 = y - FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), D_1F800000.view.effect.params[1]);
        prim->x3 = x + 16;
        prim->y3 = y - FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), D_1F800000.view.effect.params[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        setRGB3(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]), LOHU(D_1F800000.view.effect.params[7]));
        GFX_AddPrim(2, sizeof(POLY_G4));

        x += 16;
    }
}

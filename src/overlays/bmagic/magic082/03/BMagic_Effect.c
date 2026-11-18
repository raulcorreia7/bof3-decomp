#include "magic082_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    u8           i;
    u8           slot;
    PartyMember* actor;
    u16*         dst;
    u16*         src;

    actor          = g_Battle.selected_actor;
    g_Task->facing = actor->facing;
    WorldPos_Copy(&g_Task->pos, &actor->pos);
    g_Task->unk_04       = func_801EF3A0();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    slot = Battle_AllocEffect(1, 5);
    {
        PartyMember* work;

        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = g_Task->unk_04;
        g_BattleEffects[slot].arg.unk_09   = 0;
    }
    {
        PartyMember* work;

        work                        = g_Task;
        g_BattleEffects[slot].pos.x = work->pos.x;
        g_BattleEffects[slot].pos.y = work->pos.y;
        g_BattleEffects[slot].pos.z = work->pos.z;
        work->param.unk_0B += 1;
    }
    for (i = 0; i < 4; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 5);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = g_Task->unk_04;
        g_BattleEffects[slot].unk_0B       = i * 8;
        g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
        g_BattleEffects[slot].unk_0A       = g_Task->unk_09;
        g_Task->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionSE(EMI_SE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

/* func_801EF0C4 */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(2);
}

MATCH void func_801EF10C(void) {
    u8  timer;
    u32 slot;
    /* FAKE: retail frame reserves 0x10 bytes no statement uses; pure C differs only in the frame (0x18 against 0x28). */
    FAKE_STACK_PADS(u8, 0x10);

    g_PaletteFades[g_Task->timer].offset.r -= 1;
    g_PaletteFades[g_Task->timer].offset.g -= 1;
    g_PaletteFades[g_Task->timer].offset.b -= 1;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        if (Battle_CanTarget(D_800B6BF0[g_Task->unk_04], g_Battle.target_selector) & BYTE_MASK) {
            slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].unk_04       = g_Task->unk_04;
            g_BattleEffects[slot].arg.unk_09   = 1;
            g_BattleEffects[slot].unk_0A       = 0;
            g_Task->param.unk_0B++;
        } else {
            slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].unk_04       = 8;
            g_BattleEffects[slot].arg.unk_09   = 1;
            g_BattleEffects[slot].unk_0A       = 0;
            g_Task->param.unk_0B++;
        }
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF3A0(void) {
    s32 result;

    if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_Battle.action_id)) {
            case ABILITY_PROTECT:
            case ABILITY_PROTECT_SKILL:
                result = 0;
                break;
            case ABILITY_SPEED:
            case ABILITY_SPEED_SKILL:
                result = 1;
                break;
            case ABILITY_STEROIDS:
            case ABILITY_MAGIC_BELT:
            case ABILITY_MIGHT:
            case ABILITY_MIGHT_SKILL:
                result = 2;
                break;
            default:
                result = 3;
                break;
        }
    } else {
        switch (LOHU(g_Battle.action_id)) {
            case 0x10B:
                g_Battle.action_id = ABILITY_PROTECT;
                result             = 0;
                break;
            case 0x211:
                g_Battle.action_id = ABILITY_SPEED;
                result             = 1;
                break;
            case 0x14:
            case 0x117:
                g_Battle.action_id = ABILITY_MIGHT;
                result             = 2;
                break;
            default:
                result = 3;
                break;
        }
    }
    return result;
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF56C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF5B0(void) {
    SYS_DISPATCH_BYTE(D_801F0D1C, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EFA00();
        func_801EF720();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

/* Draw the magic082 disc as a fan of sixteen shaded triangles, grey at the centre and tinted
 * at the rim by the colour row the effect picks, both scaled by the effect timer byte. */
MATCH void func_801EF720(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s16*     shade;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[3] = g_Task->unk_09 * 5;
    g_ScratchPad.cells.halves[4] = D_801F0CFC[g_Task->unk_04][0] * g_Task->unk_09;
    g_ScratchPad.cells.halves[5] = D_801F0CFC[g_Task->unk_04][1] * g_Task->unk_09;
    g_ScratchPad.cells.halves[6] = D_801F0CFC[g_Task->unk_04][2] * g_Task->unk_09;
    shade                        = &g_ScratchPad.cells.halves[3];
    g_ScratchPadVectors[2].vx    = (u32)rsin(0) >> 5;
    g_ScratchPadVectors[2].vy    = (u32)rcos(0) >> 5;
    for (i = 1; i <= 16; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[2].vx = (u32)rsin(i << 8) >> 5;
        g_ScratchPadVectors[2].vy = (u32)rcos(i << 8) >> 5;
        prim                      = (POLY_G3*)g_GfxPrimCursor;
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, shade[0], shade[0], shade[0]);
        setRGB1(prim, shade[1], shade[2], shade[3]);
        setRGB2(prim, shade[1], shade[2], shade[3]);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* Draw the magic082 ring as sixteen shaded quads between two radii, tinted at the inner edge
 * by the second colour table and dark at the outer one. */
MATCH void func_801EFA00(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[4] = D_801F0D08[g_Task->unk_04][0] * g_Task->unk_09;
    g_ScratchPad.cells.halves[5] = D_801F0D08[g_Task->unk_04][1] * g_Task->unk_09;
    g_ScratchPad.cells.halves[6] = D_801F0D08[g_Task->unk_04][2] * g_Task->unk_09;
    g_ScratchPadVectors[1].vx    = (u32)rsin(0) >> 5;
    g_ScratchPadVectors[1].vy    = (u32)rcos(0) >> 5;
    g_ScratchPadVectors[3].vx    = (u32)rsin(0) >> 4;
    g_ScratchPadVectors[3].vy    = (u32)rcos(0) >> 4;
    for (i = 1; i <= 16; i++) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vx = (u32)rsin(i << 8) >> 5;
        g_ScratchPadVectors[1].vy = (u32)rcos(i << 8) >> 5;
        g_ScratchPadVectors[3].vx = (u32)rsin(i << 8) >> 4;
        g_ScratchPadVectors[3].vy = (u32)rcos(i << 8) >> 4;
        prim                      = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPadVectors[3].vz = 0;
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EFD30(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Task);
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_LaunchFromRing.h"

MATCH void func_801EFEF4(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    func_801F0A84((RANDOM_MASK(3)) | 0x18);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F03E0);
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        reset         = g_Task;
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFFE8(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;

    Battle_ProjectRange();
    func_801F0A84((RANDOM_MASK(3)) | 0x18);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F03E0);
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->timer = 28 - g_Task->param.unk_0B;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F00DC(void) {
    s32 value;
    s32 value2;
    u8  value3;

    Battle_ProjectRange();
    if ((g_Task->unk_0C == 4) && (g_Task->timer < 5U)) {
        value2 = RANDOM_MASK(3) | 0x40;
    } else {
        value2 = RANDOM_MASK(3) | 0x18;
    }
    func_801F0A84(value2);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F03E0);
    if (g_Task->unk_0C < 4) {
        value          = g_Task->unk_10 + 1;
        g_Task->unk_10 = value;
        if (!(value & 0x7)) {
            g_Task->unk_0C += 1;
        }
    }
    g_Task->unk_09 += g_Task->unk_0C;
    if (g_Task->unk_0C == 4) {
        value3        = g_Task->timer - 1;
        g_Task->timer = value3;
        if (!(value3 & BYTE_MASK)) {
            if (g_Task->param.unk_0B == 0) {
                SND_QueueSelectionSE(0x101);
            }
            g_Task->unk_10 = 8;
            g_Task->unk_14 = 8;
            g_Task->unk_20 = 8;
            g_Task->header.step += 1;
        }
    }
}

MATCH void func_801F0260(void) {
    s16* angle;
    u16  phase;
    u8   count;

    Battle_ProjectRange();
    func_801F0A84(RANDOM_MASK(3) | 0x20);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F03E0);
    g_Task->unk_10 += 4;
    g_Task->unk_09 += g_Task->unk_0C;
    phase                = g_Task->param.unk_0B + 2;
    g_Task->param.unk_0B = phase;
    phase &= 0x1F;
    angle               = &D_1F800004;
    *angle              = phase << 7;
    g_ScratchPadHalves  = g_Task->timer * g_Task->unk_10 + 0xB0;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin(phase << 7) * g_ScratchPadHalves) >> 3);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle) * g_ScratchPadHalves) >> 3);
    count               = g_Task->timer + 1;
    g_Task->timer       = count;
    if (count == 0x10) {
        g_BattleEffectBattler->param.unk_0B--;
        Effect_Reset();
    }
}

/* Draw the magic082 shell as two fans of four flat triangles, one above and one below the
 * effect, each shaded from its colour table and linked into the map cell by depth. */
MATCH void func_801F03E0(void) {
    POLY_G3* prim;
    u8*      base;
    long     depth;
    long     flag;
    s32      values[16];
    s32      i;
    s32      tpage;
    s32      x;
    s32      y;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    base = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[1] = 0x50;
        g_ScratchPad.cells.halves[0] = 0x30;
        g_ScratchPad.cells.halves[7] = (i - g_Task->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0C9C[g_Task->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0C9C[g_Task->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0C9C[g_Task->unk_04][g_ScratchPad.cells.halves[7]][2];
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPadVectors[0].vy    = 0;
        g_ScratchPadVectors[0].vz    = g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[2] = (i & 0x1F) << 7;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = 0;
        g_ScratchPad.cells.halves[2] = ((i + 8) & 0x1F) << 7;
        g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz    = 0;
        prim                         = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        values[(i - g_Task->unk_09) / 8] = RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = g_Task->pos.x.fixed;
    y = g_Task->pos.y.fixed;
    func_800AF0F8(x, y, values, base, 4, sizeof(POLY_G3), 2);
    base = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        g_ScratchPad.cells.halves[7] = (i - g_Task->unk_09) / 8;
        g_ScratchPad.cells.halves[4] = D_801F0CCC[g_Task->unk_04][g_ScratchPad.cells.halves[7]][0];
        g_ScratchPad.cells.halves[5] = D_801F0CCC[g_Task->unk_04][g_ScratchPad.cells.halves[7]][1];
        g_ScratchPad.cells.halves[6] = D_801F0CCC[g_Task->unk_04][g_ScratchPad.cells.halves[7]][2];
        g_ScratchPadVectors[0].vx    = 0;
        g_ScratchPadVectors[0].vy    = 0;
        g_ScratchPadVectors[0].vz    = -g_ScratchPad.cells.halves[1];
        g_ScratchPad.cells.halves[2] = (i & 0x1F) << 7;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = 0;
        g_ScratchPad.cells.halves[2] = ((i + 8) & 0x1F) << 7;
        g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vz    = 0;
        prim                         = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        values[(i - g_Task->unk_09) / 8] = RotAverage3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = g_Task->pos.x.fixed;
    y = g_Task->pos.y.fixed;
    func_800AF0F8(x, y, values, base, 4, sizeof(POLY_G3), 2);
}

/* Draws a semi-transparent disc of the given radius round the effect's screen point as eight
 * shaded triangles, bright at the centre and dark at the rim. */
MATCH void func_801F0A84(s32 radius) {
    POLY_G3* prim;
    s32      tpage;
    s32      i;

    g_ScratchPad.cells.halves[0] = radius;
    i                            = 0;
    do {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.value, g_Task->unk_30.value, g_Task->unk_2E.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               g_Task->unk_30.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), g_Task->unk_2E.value + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]),
               g_Task->unk_30.value + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, 0x80, 0x80, 0x80);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}

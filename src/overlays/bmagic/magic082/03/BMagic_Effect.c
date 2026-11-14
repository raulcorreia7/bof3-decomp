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
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
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

    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    g_PaletteFades[g_Task->timer].offset.blue -= 1;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        if (func_800AED5C(D_800B6BF0[g_Task->unk_04], g_Battle.target_selector) & BYTE_MASK) {
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

INCLUDE_ASM(func_801EF3A0);

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

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[3] = g_Task->unk_09 * 5;
    D_1F800000.view.effect.params[4] = D_801F0CFC[g_Task->unk_04][0] * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = D_801F0CFC[g_Task->unk_04][1] * g_Task->unk_09;
    D_1F800000.view.effect.params[6] = D_801F0CFC[g_Task->unk_04][2] * g_Task->unk_09;
    shade                            = &D_1F800000.view.effect.params[3];
    D_1F800014[2].vx                 = (u32)rsin(0) >> 5;
    D_1F800014[2].vy                 = (u32)rcos(0) >> 5;
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = (u32)rsin(i << 8) >> 5;
        D_1F800014[2].vy = (u32)rcos(i << 8) >> 5;
        prim             = (POLY_G3*)g_GfxPrimCursor;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, shade[0], shade[0], shade[0]);
        setRGB1(prim, shade[1], shade[2], shade[3]);
        setRGB2(prim, shade[1], shade[2], shade[3]);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

/* Draw the magic082 ring as sixteen shaded quads between two radii, tinted at the inner edge
 * by the second colour table and dark at the outer one. */
MATCH void func_801EFA00(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[4] = D_801F0D08[g_Task->unk_04][0] * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = D_801F0D08[g_Task->unk_04][1] * g_Task->unk_09;
    D_1F800000.view.effect.params[6] = D_801F0D08[g_Task->unk_04][2] * g_Task->unk_09;
    D_1F800014[1].vx                 = (u32)rsin(0) >> 5;
    D_1F800014[1].vy                 = (u32)rcos(0) >> 5;
    D_1F800014[3].vx                 = (u32)rsin(0) >> 4;
    D_1F800014[3].vy                 = (u32)rcos(0) >> 4;
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[1].vx = (u32)rsin(i << 8) >> 5;
        D_1F800014[1].vy = (u32)rcos(i << 8) >> 5;
        D_1F800014[3].vx = (u32)rsin(i << 8) >> 4;
        D_1F800014[3].vy = (u32)rcos(i << 8) >> 4;
        prim             = (POLY_G4*)g_GfxPrimCursor;
        D_1F800014[3].vz = 0;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EFD30(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Task);
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

INCLUDE_ASM(func_801EFDC0);

MATCH void func_801EFEF4(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    func_801F0A84((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F03E0();
    PopMatrix();
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
    Effect_SetActorMatrix();
    func_801F03E0();
    PopMatrix();
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
    Effect_SetActorMatrix();
    func_801F03E0();
    PopMatrix();
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
                SND_QueueSelectionEffect(0x101);
            }
            g_Task->unk_10 = 8;
            g_Task->unk_14 = 8;
            g_Task->unk_20 = 8;
            g_Task->header.step += 1;
        }
    }
}

INCLUDE_ASM(func_801F0260);

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

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    base = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        D_1F800000.view.effect.params[1] = 0x50;
        D_1F800000.view.effect.params[0] = 0x30;
        D_1F800000.view.effect.params[7] = (i - g_Task->unk_09) / 8;
        D_1F800000.view.effect.params[4] = D_801F0C9C[g_Task->unk_04][D_1F800000.view.effect.params[7]][0];
        D_1F800000.view.effect.params[5] = D_801F0C9C[g_Task->unk_04][D_1F800000.view.effect.params[7]][1];
        D_1F800000.view.effect.params[6] = D_801F0C9C[g_Task->unk_04][D_1F800000.view.effect.params[7]][2];
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = 0;
        D_1F800014[0].vz                 = D_1F800000.view.effect.params[1];
        D_1F800000.view.effect.params[2] = (i & 0x1F) << 7;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = 0;
        D_1F800000.view.effect.params[2] = ((i + 8) & 0x1F) << 7;
        D_1F800014[2].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz                 = 0;
        prim                             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        values[(i - g_Task->unk_09) / 8] = RotAverage3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = g_Task->pos.x.fixed;
    y = g_Task->pos.y.fixed;
    func_800AF0F8(x, y, values, base, 4, sizeof(POLY_G3), 2);
    base = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        D_1F800000.view.effect.params[7] = (i - g_Task->unk_09) / 8;
        D_1F800000.view.effect.params[4] = D_801F0CCC[g_Task->unk_04][D_1F800000.view.effect.params[7]][0];
        D_1F800000.view.effect.params[5] = D_801F0CCC[g_Task->unk_04][D_1F800000.view.effect.params[7]][1];
        D_1F800000.view.effect.params[6] = D_801F0CCC[g_Task->unk_04][D_1F800000.view.effect.params[7]][2];
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = 0;
        D_1F800014[0].vz                 = -D_1F800000.view.effect.params[1];
        D_1F800000.view.effect.params[2] = (i & 0x1F) << 7;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = 0;
        D_1F800000.view.effect.params[2] = ((i + 8) & 0x1F) << 7;
        D_1F800014[2].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz                 = 0;
        prim                             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        values[(i - g_Task->unk_09) / 8] = RotAverage3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
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

    D_1F800000.view.effect.params[0] = radius;
    i                                = 0;
    do {
        if (GetGraphType() == 1 || GetGraphType() == 2) {
            tpage = 0xA5;
        } else {
            tpage = 0x35;
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = g_Task->unk_2E.half;
        prim->y0 = g_Task->unk_30.half;
        prim->x1 = g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        prim->y1 = g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        prim->x2 = g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[0]);
        prim->y2 = g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[0]);
        setRGB0(prim, 0x80, 0x80, 0x80);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 8);
}

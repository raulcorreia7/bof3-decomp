#include "magic151_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EECB0);

MATCH void func_801EEDE0(void) {
    Callback handlers[2] = {func_801EEE38, func_801EF318};

    SYS_DISPATCH_TASK(handlers, 2, g_Task);
}

MATCH void func_801EEE38(void) {
    Magic151Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.steps, 3, g_Task);
}

MATCH void func_801EEEA8(void) {
    PartyBattler* saved_work;
    PartyBattler* battler;

    saved_work = g_Task;
    battler    = &g_BattlePartyBattlers[g_BattleActiveBattler];
    g_Task     = battler;
    Actor_RequestScript((battler->facing + 0x3C) & 0xFF);
    g_Task = saved_work;
    saved_work->unk_03 += 1;
}

INCLUDE_ASM(func_801EEF24);

INCLUDE_ASM(func_801EF070);

INCLUDE_ASM(func_801EF138);

MATCH void func_801EF2A0(void) {
    PartyBattler* saved_work;
    PartyBattler* battler;

    saved_work = g_Task;
    battler    = &g_BattlePartyBattlers[g_BattleActiveBattler];
    g_Task     = battler;
    battler->header.flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
    g_Task = saved_work;
    saved_work->header.mode += 1;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}

MATCH void func_801EF318(void) {
    Magic151Steps handlers;

    handlers = D_801EEC24;
    SYS_DISPATCH_TASK(handlers.steps, 3, g_Task);
}

INCLUDE_ASM(func_801EF388);

INCLUDE_ASM(func_801EF484);

INCLUDE_ASM(func_801EF938);

MATCH void func_801EF9F0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK_BYTES[1]);
}

MATCH void func_801EFA34(void) {
    BMagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC38, header.step);
}

INCLUDE_ASM(func_801EFAAC);

INCLUDE_ASM(func_801EFBAC);

INCLUDE_ASM(func_801EFC68);

MATCH void func_801EFD24(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 1;
        g_Task->header.step              = g_Task->header.step + 1;
    }
}

MATCH void func_801EFD80(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->header.mode == 2) {
        work              = SP_REF(PartyBattler*, 0x44u);
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EFDC0(void) {
    if (g_Task->param.unk_0B == 0) {
        g_BattleEffectBattler->param.unk_0B = 2;
        func_801E5988();
    }
}

MATCH void func_801EFE00(void) {
    SYS_DISPATCH_BYTE(D_801F24B8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F026C();
        func_801F0648();
        PopMatrix();
    }
}

MATCH void func_801EFE90(void) {
    PartyBattler* work  = g_Task;
    PartyBattler* actor = g_BattleEffectBattler;
    s32           z;

    work->pos.x.fixed    = actor->pos.x.fixed;
    work->pos.y.fixed    = actor->pos.y.fixed;
    z                    = actor->pos.z.fixed;
    work->unk_5D         = 0x10;
    work->pos.z.fixed    = z;
    g_Task->unk_5E       = 0x10;
    g_Task->unk_5F       = 0x24;
    g_Task->unk_04       = 0;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 0x1E;
    g_Task->header.step += 1;
}

MATCH void func_801EFF44(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if (timer == 32) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

INCLUDE_ASM(func_801EFF94);

#include "overlays/bmagic/Effect_StepOnZeroTick.h"

MATCH void func_801F00E8(void) {
    u8 temp_v1;

    temp_v1        = g_Task->unk_5D - 1;
    g_Task->unk_5D = temp_v1;
    if ((s8)temp_v1 == 8) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F013C(void) {
    s8 count;
    u8 count_next;

    count = g_Task->unk_5D;
    if (count != 0) {
        g_Task->unk_5D = count - 1;
    }
    count_next     = g_Task->unk_5E - 1;
    g_Task->unk_5E = count_next;
    if ((count_next << 0x18) == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801F026C);

INCLUDE_ASM(func_801F0648);

INCLUDE_ASM(func_801F0AC8);

MATCH void func_801F0BA8(void) {
    PartyBattler* work;
    s32           value;

    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    value                = RANDOM_MASK(0x1F);
    work                 = g_Task;
    work->unk_5D         = 0x10;
    work->unk_0C         = value;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 4;
    g_Task->header.step += 1;
}

MATCH void func_801F0C50(void) {
    u8 timer_next;

    timer_next    = g_Task->timer + 4;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) >= 0x20U) {
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0CB0(void) {
    PartyBattler* work;
    s8            timer;

    work         = g_Task;
    timer        = work->unk_5D - 2;
    work->unk_5D = timer;
    if (timer == 0) {
        work               = g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0D0C);

INCLUDE_ASM(func_801F10E8);

MATCH void func_801F11E0(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
        g_Task->param.unk_0B = RANDOM_MASK(0xF);
        g_Task->unk_09       = 0;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F129C(void) {
    g_Task->param.unk_0B += 1;
    g_Task->timer += 4;
    if (g_Task->timer == 0x10) {
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_Wait.h"

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixQuarterRoll.h"

INCLUDE_ASM(func_801F14D0);

MATCH void func_801F1C3C(void) {
    SYS_DISPATCH_BYTE(D_801F250C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F1DC0();
        BMagic_DrawGlowRingInner();
        BMagic_DrawGlowRingOuter();
        PopMatrix();
    }
}

MATCH void func_801F1CCC(void) {
    PartyBattler* work  = g_Task;
    PartyBattler* actor = g_BattleEffectBattler;
    s32           z;

    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->unk_09      = 0x10;
    work->unk_14      = 0x100;
    work->pos.z.fixed = z;
    g_Task->header.step += 1;
}

MATCH void func_801F1D28(void) {
    PartyBattler* work;
    s32           value;

    work         = g_Task;
    value        = work->unk_14 + 0x80;
    work->unk_14 = value;
    if (value == 0x400) {
        work->header.step++;
    }
}

/* Best 7 differences: lui a0 at 0x801F1D60; adjust register allocation. */
MATCH void func_801F1D60(void) {
    PartyBattler* work = g_Task;
    u8            timer;

    work->unk_14 += 0x20;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void Effect_SetActorMatrix_801F1DC0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

/* The glow ring scratch: the inner radius, the outer radius and the shade, then the quad corners (D_1F800014). */
#define GLOW_RING_INNER D_1F800000_HALF[1]
#define GLOW_RING_OUTER D_1F800000_HALF[2]
#define GLOW_RING_SHADE D_1F800000_HALF[5]

/* The inner half of the glow ring: a ring of 64 additive quads from the effect radius (word 0x14) out
 * to 64 past it, brightest at its outer edge. */
MATCH void BMagic_DrawGlowRingInner(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    GFX_AddPrim(4, 0xC);
    GLOW_RING_INNER  = g_Task->unk_14;
    GLOW_RING_OUTER  = g_Task->unk_14 + 0x40;
    GLOW_RING_SHADE  = g_Task->unk_09 * 15;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    D_1F800014[3].vz = 0;
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 64; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_OUTER);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0,
                      (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB1(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(4, 0x24);
    }
}

/* The outer half of the glow ring: the ring from 64 to 128 past the effect radius, fading out at its outer edge. */
MATCH void BMagic_DrawGlowRingOuter(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    GFX_AddPrim(4, 0xC);
    GLOW_RING_INNER  = g_Task->unk_14 + 0x40;
    GLOW_RING_OUTER  = g_Task->unk_14 + 0x80;
    GLOW_RING_SHADE  = g_Task->unk_09 * 15;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    D_1F800014[3].vz = 0;
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 64; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_OUTER);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 6), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 6), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0,
                      (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        setRGB3(prim, GLOW_RING_SHADE, GLOW_RING_SHADE, GLOW_RING_SHADE);
        GFX_AddPrim(4, 0x24);
    }
}

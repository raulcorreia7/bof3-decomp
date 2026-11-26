#include "magic125_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_MarkDamagedOnZeroTick);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, func_801EFB48);
}

MATCH void func_801EED04(void) {
    u8 slot;
    u8 i;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 92);
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 1;
    SELF(PartyMember)->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 92);
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].arg.unk_09   = 9;
    SELF(PartyMember)->param.unk_0B += 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEEC0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF04(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 2), 2, g_Self);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        if ((g_FrameCount & 0x1) == 0) {
            SELF(PartyMember)->unk_5D = (RANDOM_MASK(3)) + 4;
            SELF(PartyMember)->unk_5E = (RANDOM_MASK(3)) + 4;
            SELF(PartyMember)->unk_5F = (RANDOM_MASK(3)) + 4;
        }
        Effect_SetActorMatrix();
        func_801EF258();
        func_801EF508();
        PopMatrix();
    }
}

MATCH void func_801EEFF8(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x04000000;
        SELF(PartyMember)->unk_5D      = (RANDOM_MASK(3)) + 4;
        SELF(PartyMember)->unk_5E      = (RANDOM_MASK(3)) + 4;
        SELF(PartyMember)->unk_5F      = (RANDOM_MASK(3)) + 4;
        SELF(PartyMember)->unk_14      = 0x100;
        SELF(PartyMember)->unk_09      = 0x10;
        SELF(PartyMember)->timer       = 8;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EF0F8 */
MATCH void Effect_Rise(void) {
    PartyMember* work  = SELF(PartyMember);
    u8           timer = work->timer - 1;
    work->timer        = timer;
    work->pos.z.fixed += TO_COORD(-128);
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EF148 */
#include "overlays/bmagic/shared/Effect_RiseUntilTimerZero.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801EF258(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_14;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[3] = (s8)SELF(PartyMember)->unk_5D * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[4] = (s8)SELF(PartyMember)->unk_5E * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5F * SELF(PartyMember)->unk_09;
    for (i = 1; i <= 16; i++) {
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        prim                      = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, 0x10, 0x10, 0x10);
        setRGB2(prim, 0x10, 0x10, 0x10);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EF508(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_14;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[3] = (s8)SELF(PartyMember)->unk_5D * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[4] = (s8)SELF(PartyMember)->unk_5E * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5F * SELF(PartyMember)->unk_09;
    for (i = 1; i <= 32; i++) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz = -0x300;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz = -0x300;
        g_ScratchPadVectors[3].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[3].vz = 0;
        x                         = (g_ScratchPadVectors[1].vx << 9) + SELF(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[1].vy << 9) + SELF(PartyMember)->pos.y.fixed;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(x, y, 0, sizeof(POLY_G4));
    }
}

MATCH void func_801EF808(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F05EC, func_801EF508);
}

MATCH void func_801EF890(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->unk_5D      = 0xF;
        SELF(PartyMember)->unk_5E      = 0xF;
        SELF(PartyMember)->unk_5F      = 0xF;
        SELF(PartyMember)->unk_14      = 0x100;
        SELF(PartyMember)->unk_20      = 0x21;
        SELF(PartyMember)->unk_09      = 0x10;
        SELF(PartyMember)->timer       = 30;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF960(void) {
    PartyMember* battler;
    s32          speed;
    u8           i;
    u8           slot;

    speed = SELF(PartyMember)->unk_20;
    if (speed != 1) {
        SELF(PartyMember)->unk_20 = speed - 2;
    }
    SELF(PartyMember)->unk_14 -= SELF(PartyMember)->unk_20;
    if (SELF(PartyMember)->unk_14 < 0x30) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x01));
        for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
            slot                                   = BMagic_AllocEffect();
            battler                                = g_BattleEffectBattler;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (i / 6) * 8 + (rand() & 7) + 1;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFAB0(void) {
    s32 level;
    u8  counter;

    level = SELF(PartyMember)->unk_14;
    if (level >= 9) {
        SELF(PartyMember)->unk_14 = level - 1;
    }
    if (g_FrameCount & 0x1) {
        counter                   = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
            Effect_Reset();
        }
    }
}

MATCH void func_801EFB48(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 8), 1, g_Self);
}

MATCH void func_801EFB8C(void) {
    s32 tpage;

    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 9), SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        func_800AF764();
        func_801EFFC8();
        func_801F020C();
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    }
}

MATCH void func_801EFCE4(void) {
    s32 phase;

    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->unk_0C      = 5 * ONE;
        SELF(PartyMember)->unk_18      = ONE / 8;
        SELF(PartyMember)->unk_14      = TO_COORD(8);
        SELF(PartyMember)->unk_20      = TO_COORD(4);
        g_ScratchPad.cells.halves[0]   = SELF(PartyMember)->unk_0C;
        phase                          = (SELF(PartyMember)->param.unk_0B & 7) * 8 + SELF(PartyMember)->unk_09;
        g_ScratchPad.cells.halves[2]   = BMAGIC_PHASE_ANGLE(phase);
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin((s16)BMAGIC_PHASE_ANGLE(phase)), g_ScratchPad.cells.halves[0]);
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->unk_5D      = (rand() & 7) + 5;
        SELF(PartyMember)->unk_5E      = (rand() & 7) + 5;
        SELF(PartyMember)->unk_5F      = (rand() & 7) + 5;
        SELF(PartyMember)->unk_09      = 0;
        SELF(PartyMember)->timer       = 24;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Orbits the effect around its battler, the radius shrinking each frame, and releases the battler once the radius is gone. */
MATCH void func_801EFE8C(void) {
    s32 phase;

    SELF(PartyMember)->unk_09 += 1;
    SELF(PartyMember)->unk_0C -= SELF(PartyMember)->unk_18;
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_0C;
    phase                        = (SELF(PartyMember)->param.unk_0B & 7) * 8 + SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[2] = BMAGIC_PHASE_ANGLE(phase);
    SELF(PartyMember)->pos.x.fixed += FIXED_MUL(rsin((s16)BMAGIC_PHASE_ANGLE(phase)), g_ScratchPad.cells.halves[0]);
    SELF(PartyMember)->pos.y.fixed += FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
    SELF(PartyMember)->pos.z.fixed += SELF(PartyMember)->unk_14;
    if (SELF(PartyMember)->unk_0C == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

MATCH void func_801EFFC8(void) {
    POLY_G3* prim;
    s32      i;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer;
    g_ScratchPadVectors[0].vx    = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[0].vy    = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPad.cells.halves[3] = (s8)SELF(PartyMember)->unk_5D * 16;
    g_ScratchPad.cells.halves[4] = (s8)SELF(PartyMember)->unk_5E * 16;
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5F * 16;
    for (i = 1; i < 9; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value, g_ScratchPadVectors[0].vx, g_ScratchPadVectors[0].vy);
        g_ScratchPadVectors[0].vx = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]);
        prim->x2                  = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[0].vy = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]);
        prim->y2                  = g_ScratchPadVectors[0].vy;
        setRGB0(prim, 0xF0, 0xF0, 0xF0);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

MATCH void func_801F020C(void) {
    POLY_G4* prim;
    s32      i;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->timer * 2;
    g_ScratchPadVectors[0].vx    = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[0].vy    = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[1].vx    = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    for (i = 1; i < 9; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_ScratchPadVectors[0].vx, g_ScratchPadVectors[0].vy);
        prim->x2                  = g_ScratchPadVectors[1].vx;
        prim->y2                  = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vx = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[1]);
        prim->x1                  = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[0].vy = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[1]);
        prim->y1                  = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[1].vx = SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]);
        prim->x3                  = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[1].vy = SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]);
        prim->y3                  = g_ScratchPadVectors[1].vy;
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

/* func_801F0524 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0588 */
#include "overlays/bmagic/shared/Actor_Clear.h"

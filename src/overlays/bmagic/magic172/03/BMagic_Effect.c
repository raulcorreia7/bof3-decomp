#include "magic172_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {BMagic_MagicBallInit, Effect_MarkDamagedOnZeroTick};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

/* func_801EEC5C */
MATCH void BMagic_MagicBallInit(void) {
    PartyMember* work;
    PartyMember* target;
    u8           slot;
    u32          first_slot;
    u32          i;

    TASK(PartyMember)->facing       = g_BattleEffectBattler->facing;
    TASK(PartyMember)->pos.x        = g_BattleEffectBattler->pos.x;
    TASK(PartyMember)->pos.y        = g_BattleEffectBattler->pos.y;
    TASK(PartyMember)->pos.z        = g_BattleEffectBattler->pos.z;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    first_slot                               = Battle_AllocEffect(1, 0x51) & BYTE_MASK;
    work                                     = TASK(PartyMember);
    g_BattleEffects[first_slot].header.mode  = 0;
    g_BattleEffects[first_slot].target.party = work;
    TASK(PartyMember)->param.unk_0B += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x51);
        target                             = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_04       = first_slot;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].target.party = target;
        TASK(PartyMember)->param.unk_0B += 1;
        i++;
    } while (i < 8);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEE38 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EEE7C */
MATCH void BMagic_MagicBallCoreUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicMagicBallCoreSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        switch (TASK(PartyMember)->header.step) {
            /* FAKE: retail compare tree needs a third case below 2 on the default body; the bytes do not say which step. */
            case 1:
            default:
                Battle_ProjectRange();
                BMagic_MagicBallDrawBoltWide(rand() & 0x1FF, 3);
                BMagic_MagicBallDrawBoltNarrow((rand() & 0x1FF) + 0x333, 3);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0x666, 3);
                BMagic_MagicBallDrawBoltNarrow((rand() & 0x1FF) + 0x999, 3);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0xCCC, 3);
                BMagic_MagicBallDrawDisc();
                BMagic_MagicBallDrawRing();
                break;
            case 2:
                Battle_ProjectRange();
                BMagic_MagicBallDrawBoltWide(rand() & 0x1FF, 7);
                BMagic_MagicBallDrawBoltNarrow((rand() & 0x1FF) + 0x333, 7);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0x666, 7);
                BMagic_MagicBallDrawBoltNarrow((rand() & 0x1FF) + 0x999, 7);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0xCCC, 7);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0x400, 15);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0x800, 15);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0xC14, 15);
                BMagic_MagicBallDrawDisc();
                BMagic_MagicBallDrawRing();
                BMagic_MagicBallDrawWaveInner();
                BMagic_MagicBallDrawWaveOuter();
                break;
            case 3:
                Battle_ProjectRange();
                BMagic_MagicBallDrawWaveInner();
                BMagic_MagicBallDrawWaveOuter();
                break;
            case 4:
                Battle_ProjectRange();
                BMagic_MagicBallDrawBoltWide(rand() & 0x1FF, 3);
                BMagic_MagicBallDrawBoltNarrow((rand() & 0x1FF) + 0x333, 3);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0x666, 3);
                BMagic_MagicBallDrawBoltNarrow((rand() & 0x1FF) + 0x999, 3);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0xCCC, 3);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0x400, 7);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0x800, 7);
                BMagic_MagicBallDrawBoltWide((rand() & 0x1FF) + 0xC14, 7);
                break;
        }
    }
}

MATCH void func_801EF158(void) {
    PartyMember* actor;
    PartyMember* work;
    s32          angle;

    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
    actor                          = g_Battle.selected_actor;
    angle                          = ratan2(actor->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, actor->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
    work                           = TASK(PartyMember);
    work->param.unk_0B             = 0;
    work->unk_0C                   = angle;
    TASK(PartyMember)->unk_09      = 0;
    TASK(PartyMember)->timer       = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF210(void) {
    VECTOR       pos;
    PartyMember* actor;
    s32          diff;
    u8           count;

    count = TASK(PartyMember)->unk_09;
    if (count < 16) {
        TASK(PartyMember)->unk_09 = count + 4;
    }
    actor = g_Battle.selected_actor;
    setVector(&pos, (actor->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.z.fixed + TO_COORD(256)) >> 17);
    Battle_StepRangeToward(pos, 0x40);
    TASK(PartyMember)->unk_10 = TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->unk_0C = ratan2(actor->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, actor->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
    if (func_800AF66C((BattleRange*)actor, 0x8000) == 0) {
        diff                      = (TASK(PartyMember)->unk_10 & ANGLE_MASK) - (TASK(PartyMember)->unk_0C & ANGLE_MASK);
        TASK(PartyMember)->unk_10 = diff;
        if (diff < 0) {
            TASK(PartyMember)->unk_10 = ~diff + 1;
        }
        if ((u32)(TASK(PartyMember)->unk_10 - 0x601) >= 0x3FF) {
            return;
        }
    }
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    SND_SEQueueSelection(0x101);
    TASK(PartyMember)->unk_09 = 16;
    TASK(PartyMember)->header.step += 1;
}

/* func_801EF3A4 */
MATCH void BMagic_MagicBallCoreBurst(void) {
    u8 counter;
    u8 timer;

    TASK(PartyMember)->param.unk_0B += 2;
    timer = TASK(PartyMember)->timer;
    if (timer < 16U) {
        TASK(PartyMember)->timer = timer + 2;
    }
    counter                   = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF430 */
MATCH void BMagic_MagicBallCoreFade(void) {
    u8 timer_next;

    TASK(PartyMember)->param.unk_0B += 4;
    timer_next               = TASK(PartyMember)->timer - 2;
    TASK(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        SND_SEQueueSelection(0x102);
        TASK(PartyMember)->unk_09 = 0x10;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

/* func_801EF518 */
MATCH void BMagic_MagicBallTrailUpdate(void) {
    g_BMagicMagicBallTrailSteps[TASK(PartyMember)->header.step]();
    if (TASK(PartyMember)->header.flags & TASK(PartyMember)->header.step) {
        Battle_ProjectRange();
        BMagic_MagicBallDrawTrail();
    }
}

/* func_801EF590 */
MATCH void BMagic_MagicBallTrailPlace(void) {
    PartyMember* actor;
    PartyMember* work;
    s32          angle;

    if (--TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        actor                          = g_Battle.selected_actor;
        angle                          = ratan2(actor->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, actor->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
        work                           = TASK(PartyMember);
        work->unk_09                   = 0;
        work->unk_0C                   = angle;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF650 */
MATCH void BMagic_MagicBallTrailFly(void) {
    PartyMember* actor;
    VECTOR       pos;

    if (TASK(PartyMember)->unk_09 < 0x10) {
        TASK(PartyMember)->unk_09 += 4;
    }
    actor = g_Battle.selected_actor;
    setVector(&pos, (actor->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, (actor->pos.z.fixed + TO_COORD(256)) >> 17);
    Battle_StepRangeToward(pos, 0x40);
    TASK(PartyMember)->unk_10 = TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->unk_0C = ratan2(actor->pos.x.fixed - TASK(PartyMember)->pos.x.fixed, actor->pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
    if (g_BattleEffects[TASK(PartyMember)->unk_04].header.step == 2) {
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnTimerNegative.h"

/* func_801EF7CC */
MATCH void BMagic_MagicBallDrawDisc(void) {
    POLY_G3* prim;
    u16      x;
    u16      y;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 0;
    g_ScratchPad.cells.halves[0] = 16;
    x                            = TASK(PartyMember)->screen_x.value;
    y                            = TASK(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 * 12;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_09 * 2;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09 * 2;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->unk_09 * 14;
    for (i = 0; i < 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, x, y, x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x2                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
    }
}

/* func_801EFA2C */
MATCH void BMagic_MagicBallDrawRing(void) {
    POLY_G4* prim;
    u16      x;
    u16      y;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 0;
    g_ScratchPad.cells.halves[0] = 16;
    g_ScratchPad.cells.halves[1] = 24;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->unk_09 * 14;
    x                            = TASK(PartyMember)->screen_x.value;
    y                            = TASK(PartyMember)->screen_y.value;
    for (i = 0; i < 16; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        prim->x2                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y2                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x1                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y3                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
}

/* func_801EFD04 */
MATCH void BMagic_MagicBallDrawWaveInner(void) {
    POLY_G4* prim;
    u16      x;
    u16      y;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 0;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->param.unk_0B;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->param.unk_0B * 2;
    g_ScratchPad.cells.halves[4] = 1;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer * 6;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->timer * 8;
    x                            = TASK(PartyMember)->screen_x.value;
    y                            = TASK(PartyMember)->screen_y.value;
    for (i = 0; i < 16; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        prim->x2                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y2                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x1                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y3                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB3(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
}

/* func_801EFFE8 */
MATCH void BMagic_MagicBallDrawWaveOuter(void) {
    POLY_G4* prim;
    u16      x;
    u16      y;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 0;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->param.unk_0B * 2;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->param.unk_0B * 4;
    g_ScratchPad.cells.halves[4] = 1;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer * 5;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->timer * 8;
    x                            = TASK(PartyMember)->screen_x.value;
    y                            = TASK(PartyMember)->screen_y.value;
    for (i = 0; i < 16; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        prim->x2                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y2                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x1                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y3                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
}

/* func_801F02C8 */
MATCH void BMagic_MagicBallDrawBoltWide(s32 angle, s32 spread) {
    LINE_G2* prim;
    u16      x;
    u16      y;
    s32      i;
    s32      sine;
    s32      tpage;

    MAGIC172_DRAW_JAGGED_LINE(angle, spread, 0x7F, 12, 16);
}

/* func_801F05E8 */
MATCH void BMagic_MagicBallDrawBoltNarrow(s32 angle, s32 spread) {
    LINE_G2* prim;
    u16      x;
    u16      y;
    s32      i;
    s32      sine;
    s32      tpage;

    MAGIC172_DRAW_JAGGED_LINE(angle, spread, 0x3F, 8, 12);
}

/* func_801F0908 */
MATCH void BMagic_MagicBallDrawTrail(void) {
    POLY_G3* prim;
    u16      x;
    u16      y;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[2] = 0;
    g_ScratchPad.cells.halves[0] = 24;
    x                            = TASK(PartyMember)->screen_x.value;
    y                            = TASK(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->unk_09 * TASK(PartyMember)->param.unk_0B;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_09 * g_BMagicMagicBallTrailTints[TASK(PartyMember)->param.unk_0B].r;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = TASK(PartyMember)->unk_09 * g_BMagicMagicBallTrailTints[TASK(PartyMember)->param.unk_0B].b;
    for (i = 0; i < 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, x, y, x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x2                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));
    }
}

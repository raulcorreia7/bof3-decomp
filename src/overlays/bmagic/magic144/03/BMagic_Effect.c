#include "magic144_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC04 */
MATCH void BMagic_WallOfFireUpdate(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(BMagic_WallOfFireInit, Effect_StartOnZeroTick);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, BMagic_WallOfFireSlotUpdate);
}

/* func_801EED04 */
MATCH void BMagic_WallOfFireInit(void) {
    PartyMember* actor;
    PartyMember* task;
    u32          i;
    u32          slot;
    u16*         src;
    u16*         dst;

    TASK(PartyMember)->param.unk_0B = 0;
    BMAGIC_CLEAR_EFFECTS(i);
    actor                              = g_Battle.selected_actor;
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_WALL_OF_FIRE) & BYTE_MASK;
    i                                  = 1;
    dst                                = BATTLE_EFFECT_PALETTE_COLORS;
    src                                = BATTLE_PALETTE_SOURCE_COLORS;
    task                               = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = BMAGIC_WALL_OF_FIRE_EFFECT_TARGET;
    g_BattleEffects[slot].target.party = task;
    g_BattleEffects[slot].pos.x.fixed  = actor->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = actor->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = actor->pos.z.fixed;
    TASK(PartyMember)->param.unk_0B    = 1;
    for (; i < 16; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = 0;
    g_GfxPalettePending                                          = 1;
    TASK(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEE9C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EEEE0 */
MATCH void BMagic_WallOfFireTargetUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicWallOfFireTargetSteps, BMagic_WallOfFireDrawShadow);
}

/* func_801EEF68 */
MATCH void BMagic_WallOfFireTargetSpawn(void) {
    PartyMember* work;
    u8           i;
    u8           slot;

    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->param.unk_0B = 0;
    for (i = 0; i < 3; i++) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            work                                  = TASK(PartyMember);
            BMAGIC_EFFECT_SLOTS[slot].header.mode = (i != 0) ? BMAGIC_WALL_OF_FIRE_SLOT_GLOW : BMAGIC_WALL_OF_FIRE_SLOT_FLAME;
            BMAGIC_EFFECT_SLOTS[slot].header.step = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B      = i;
            BMAGIC_EFFECT_SLOTS[slot].header.flags |= BMAGIC_EFFECT_IN_USE | ACTOR_FLAG_HIDDEN;
            BMAGIC_EFFECT_SLOTS[slot].target.party = work;
            TASK(PartyMember)->param.unk_0B += 1;
        }
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    TASK(PartyMember)->header.step += 1;
}

/* func_801EF078 */
MATCH void BMagic_WallOfFireTargetHit(void) {
    u8            timer;
    PartyMember** actor;
    timer                     = TASK(PartyMember)->unk_09 + 2;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 16) {
        actor = &g_Battle.selected_actor;
        GFX_PaletteFreeFadeTarget(*actor);
        GFX_PaletteAllocFade(*actor, -8, -8, -8, 1);
        Battle_MarkDamaged(g_Battle.target_selector);
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StepOnOwnTickFlag.h"

/* func_801EF154 */
MATCH void BMagic_WallOfFireTargetEnd(void) {
    u8 count;

    count = TASK(PartyMember)->unk_09;
    if (count != 0) {
        TASK(PartyMember)->unk_09 = count - 1;
    }
    if (TASK(PartyMember)->param.unk_0B == 0x80) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF294 */
MATCH void BMagic_WallOfFireDrawShadow(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0x180;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    if (TASK(PartyMember)->unk_09 < 16) {
        g_ScratchPad.cells.halves[7] = TASK(PartyMember)->unk_09 << 3;
    } else {
        g_ScratchPad.cells.halves[7] = 0x80;
    }

    for (i = 1; i < 9; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801EF510 */
MATCH void BMagic_WallOfFireSlotUpdate(void) {
    SYS_DISPATCH_TASK(g_BMagicWallOfFireSlotModes, 1, g_Task);
}

/* func_801EF554 */
MATCH void BMagic_WallOfFireFlameUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicWallOfFireFlameSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        Effect_DrawFlameColumn();
    }
}

#include "overlays/bmagic/shared/Effect_StartAtTarget.h"

/* func_801EF654 */
MATCH void BMagic_WallOfFireFlameGrow(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

#include "overlays/bmagic/shared/Effect_CountUpAndMarkBattler.h"

#include "overlays/bmagic/shared/Effect_CountDownByTwoFinishAtOne.h"

/* func_801EF818 */
#include "overlays/bmagic/shared/Effect_DrawFlameColumn.h"

/* func_801EFF74 */
MATCH void BMagic_WallOfFireGlowUpdate(void) {
    PartyMember* work;
    u16          x;
    u16          y;

    SYS_DISPATCH_BYTE(g_BMagicWallOfFireGlowSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        work = TASK(PartyMember);
        if (work->param.unk_0B == 1) {
            x = work->screen_x.value - BMAGIC_WALL_OF_FIRE_GLOW_DRIFT_X;
            y = work->screen_y.value;
        } else {
            x = work->screen_x.value + BMAGIC_WALL_OF_FIRE_GLOW_DRIFT_X;
            y = work->screen_y.value;
        }
        y -= BMAGIC_WALL_OF_FIRE_GLOW_RISE_Y;
        work->screen_x.value = x;
        work->screen_y.value = y;
        BMagic_WallOfFireDrawGlow();
    }
}

#include "overlays/bmagic/shared/Effect_AppearAtTarget.h"

/* func_801F00A0 */
MATCH void BMagic_WallOfFireGlowGrow(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/shared/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/shared/Effect_TickCounter.h"

/* func_801F01D0 */
MATCH void BMagic_WallOfFireDrawGlow(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = (rand() & 0xF) + 0x40;
    g_ScratchPad.cells.halves[7] = TASK(PartyMember)->unk_09 * 10;
    for (i = 0; i < 8; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value, TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]),
               TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]),
               TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7] / 5, g_ScratchPad.cells.halves[7] / 5);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

/* func_801F046C */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

#include "magic092_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(BMagic_FireblastInit, Effect_StartOnZeroTick);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, BMagic_FireblastSlotUpdate);
}

/* Clears the effect slot table and spawns one effect 0x28 at each selectable battler, the
 * enemies when the target selector holds 0x40 and the party otherwise, each starting 16
 * frames after the one before; then sets STP on colours 1 to 15 of work palette row 26. */
/* func_801EED04 */
MATCH void BMagic_FireblastInit(void) {
    u32 i;
    u32 slot;
    u32 count;
    u8  index;
    u8  battler;

    count = 0;
    BMAGIC_CLEAR_EFFECTS(i);
    TASK(PartyMember)->param.unk_0B = 0;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index   = i;
            battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
            if (!Battle_SlotIsBlocked(battler)) {
                slot                               = Battle_AllocEffect(1, 0x28) & BYTE_MASK;
                g_BattleEffects[slot].target.party = TASK(PartyMember);
                g_BattleEffects[slot].unk_03       = index;
                g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;
                g_BattleEffects[slot].arg.unk_09   = count * BMAGIC_FIREBLAST_TARGET_DELAY + 1;
                count++;
                TASK(PartyMember)->param.unk_0B += 1;
            }
        }
    } else {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 0x28) & BYTE_MASK;
                g_BattleEffects[slot].target.party = TASK(PartyMember);
                g_BattleEffects[slot].unk_03       = i;
                g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;
                g_BattleEffects[slot].arg.unk_09   = count * BMAGIC_FIREBLAST_TARGET_DELAY + 1;
                count++;
                TASK(PartyMember)->param.unk_0B += 1;
            }
        }
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = 0;
    for (i = 1; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] | PSX_COLOR_STP_BIT;
    }
    g_GfxPalettePending = 1;
    TASK(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EF000 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EF044 */
MATCH void BMagic_FireblastTargetUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicFireblastTargetSteps, BMagic_FireblastDrawShadow);
}

/* func_801EF0CC */
MATCH void BMagic_FireblastTargetSpawn(void) {
    PartyMember* work;
    u8           count;
    u8           i;
    u8           slot;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        TASK(PartyMember)->param.unk_0B = 0;
        for (i = 0; i < 3; i++) {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                  = TASK(PartyMember);
                BMAGIC_EFFECT_SLOTS[slot].header.mode = (i != 0) ? BMAGIC_FIREBLAST_SLOT_GLOW : BMAGIC_FIREBLAST_SLOT_FLAME;
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
}

/* func_801EF1F0 */
MATCH void BMagic_FireblastTargetHit(void) {
    void* battler;
    u8    count;

    count                     = TASK(PartyMember)->unk_09 + 2;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0x10) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = &g_BattleEnemyBattlers[TASK(PartyMember)->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            Battle_ApplyDamageFlags((TASK(PartyMember)->unk_03 + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK, 0x10);
        } else {
            battler = &g_Game.members[TASK(PartyMember)->unk_03];
            GFX_PaletteFreeFadeTarget(battler);
            GFX_PaletteAllocFade(battler, -8, -8, -8, 1);
            Battle_ApplyDamageFlags(TASK(PartyMember)->unk_03, 0x10);
        }
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StepOnOwnTickFlag.h"

/* func_801EF388 */
MATCH void BMagic_FireblastTargetEnd(void) {
    u8 count;

    count = TASK(PartyMember)->unk_09;
    if (count != 0) {
        TASK(PartyMember)->unk_09 = count - 1;
    }
    if (TASK(PartyMember)->param.unk_0B == 0x80) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            GFX_PaletteFreeFadeTarget(&g_BattleEnemyBattlers[TASK(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler((TASK(PartyMember)->unk_03 + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK);
            Battle_MarkDamaged((TASK(PartyMember)->unk_03 + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK);
        } else {
            GFX_PaletteFreeFadeTarget((EnemyBattler*)&g_Game.members[TASK(PartyMember)->unk_03]);
            Battle_FadePoisonedBattler(TASK(PartyMember)->unk_03);
            Battle_MarkDamaged(TASK(PartyMember)->unk_03);
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF580 */
MATCH void BMagic_FireblastDrawShadow(void) {
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
        g_ScratchPad.cells.halves[7] = TASK(PartyMember)->unk_09 * 8;
    } else {
        g_ScratchPad.cells.halves[7] = 0x80;
    }

    for (i = 1; i <= 8; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(g_ScratchPad.cells.halves[7]), LOHU(g_ScratchPad.cells.halves[7]), LOHU(g_ScratchPad.cells.halves[7]));
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801EF7FC */
MATCH void BMagic_FireblastSlotUpdate(void) {
    SYS_DISPATCH_TASK(g_BMagicFireblastSlotModes, 1, g_Task);
}

/* func_801EF840 */
MATCH void BMagic_FireblastFlameUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicFireblastFlameSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        Effect_DrawFlameColumn();
    }
}

#include "overlays/bmagic/shared/Effect_StartAtTarget.h"

/* func_801EF940 */
MATCH void BMagic_FireblastFlameGrow(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

#include "overlays/bmagic/shared/Effect_CountUpAndMarkBattler.h"

#include "overlays/bmagic/shared/Effect_CountDownByTwoFinishAtOne.h"

/* func_801EFB04 */
#include "overlays/bmagic/shared/Effect_DrawFlameColumn.h"

/* func_801F0260 */
MATCH void BMagic_FireblastGlowUpdate(void) {
    PartyMember* work;
    u16          x;
    u16          y;

    SYS_DISPATCH_BYTE(g_BMagicFireblastGlowSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        work = TASK(PartyMember);
        if (work->param.unk_0B == 1) {
            x = work->screen_x.value - BMAGIC_FIREBLAST_GLOW_DRIFT_X;
            y = work->screen_y.value;
        } else {
            x = work->screen_x.value + BMAGIC_FIREBLAST_GLOW_DRIFT_X;
            y = work->screen_y.value;
        }
        y -= BMAGIC_FIREBLAST_GLOW_RISE_Y;
        work->screen_x.value = x;
        work->screen_y.value = y;
        BMagic_FireblastDrawGlow();
    }
}

#include "overlays/bmagic/shared/Effect_AppearAtTarget.h"

/* func_801F038C */
MATCH void BMagic_FireblastGlowGrow(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/shared/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/shared/Effect_TickCounter.h"

/* Draws the glow fan at the effect point: eight triangles of a radius 64 to 79 picked
 * once, red at the centre with a fifth of it in green and blue, redrawing the blend
 * mode for each. */
/* func_801F04BC */
MATCH void BMagic_FireblastDrawGlow(void) {
    POLY_G3* prim;
    s32      angle;
    s32      i;

    g_ScratchPad.cells.halves[0] = RANDOM_MASK(0xF) + 0x40;
    i                            = 0;
    g_ScratchPad.cells.halves[7] = TASK(PartyMember)->unk_09 * 10;
    do {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = GFX_BeginPolyG3(1);
        setXY0(prim, TASK(PartyMember)->screen_x.value, TASK(PartyMember)->screen_y.value);
        angle    = i << 9;
        prim->x1 = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(angle), g_ScratchPad.cells.halves[0]);
        prim->y1 = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(angle), g_ScratchPad.cells.halves[0]);
        i++;
        angle    = i << 9;
        prim->x2 = TASK(PartyMember)->screen_x.value + FIXED_MUL(rsin(angle), g_ScratchPad.cells.halves[0]);
        prim->y2 = TASK(PartyMember)->screen_y.value + FIXED_MUL(rcos(angle), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7] / 5, g_ScratchPad.cells.halves[7] / 5);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    } while (i < 8);
}

/* func_801F0758 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

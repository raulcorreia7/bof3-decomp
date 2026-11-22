#include "magic062_03.h"
#include "menu/clock.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    PartyMember* actor;
    u16*         dst;
    u16*         src;
    PartyMember* owner;
    PartyMember* spawner;
    u8           i;
    u8           slot;

    actor                = g_Battle.selected_actor;
    g_Task->facing       = actor->facing;
    g_Task->pos.x.fixed  = actor->pos.x.fixed;
    g_Task->pos.y.fixed  = actor->pos.y.fixed;
    g_Task->pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 74);
    owner                              = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0;
    g_BattleEffects[slot].target.party = owner;
    g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
    g_Task->param.unk_0B += 1;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 74);
        spawner                            = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i * 8;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
        g_BattleEffects[slot].target.party = spawner;
        g_BattleEffects[slot].unk_0A       = g_Task->unk_09;
        g_Task->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/shared/Effect_ReplacePaletteFade.h"

/* func_801EEF68 */
#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

/* func_801EF078 */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(2);
}

MATCH void func_801EF0C0(void) {
    s32          i;
    PartyMember* owner;
    u8           slot;

    g_PaletteFades[g_Task->timer].offset.r--;
    g_PaletteFades[g_Task->timer].offset.g--;
    g_PaletteFades[g_Task->timer].offset.b--;
    if (--g_Task->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        for (i = 0; i < 4; i++) {
            func_801EF2F0(D_800B6BF0[i]);
            slot                               = Battle_AllocEffect(1, 72);
            owner                              = g_Task;
            g_BattleEffects[slot].unk_04       = i;
            g_BattleEffects[slot].arg.unk_09   = i * 5 + 1;
            g_BattleEffects[slot].unk_0A       = i * 12 + 1;
            g_BattleEffects[slot].target.party = owner;
            g_Task->param.unk_0B++;
        }
        g_Task->header.mode++;
    }
}

MATCH void func_801EF2A0(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0) {
        flags                     = &g_Battle.flags;
        g_GameCelerityTimer.hours = 5;
        *flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF2F0(s32 stat) {
    u8  change;
    s32 delta;
    s32 value;
    /* FAKE: retail frame reserves 8 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 8);

    if (g_Battle.target_selector < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Battle.target_record = &g_Game.members[g_Battle.target_selector].u.turn;
    } else {
        g_Battle.target_record = &ENEMY_COMBATANT(g_Battle.target_selector).turn;
    }
    g_Battle.target_record->hp_change    = 0;
    g_Battle.target_record->ap_change    = 0;
    g_Battle.target_record->target_flags = 0;
    change                               = g_Abilities[g_Battle.action_id].power;
    value                                = ((s8*)g_Battle.target_record)[0x14 + (u8)stat];
    delta                                = value + (s8)change;
    if (delta > 100) {
        ((s8*)g_Battle.target_record)[0x14 + (u8)stat] = 100;
    } else if (delta < -100) {
        ((s8*)g_Battle.target_record)[0x14 + (u8)stat] = -100;
    } else {
        ((s8*)g_Battle.target_record)[0x14 + (u8)stat] = value + (s8)change;
        Battle_RescaleStats(g_Battle.target_selector);
    }
}
#else
INCLUDE_ASM(func_801EF2F0);
#endif

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF4C4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF508(void) {
    SYS_DISPATCH_BYTE(D_801F0C18, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF678();
        func_801EF934();
        PopMatrix();
    }
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801EF678(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[3] = g_Task->unk_09 * 5;
    g_ScratchPad.cells.halves[4] = ((rand() & 3) + 3) * g_Task->unk_09;
    g_ScratchPad.cells.halves[5] = ((rand() & 3) + 3) * g_Task->unk_09;
    g_ScratchPad.cells.halves[6] = ((rand() & 3) + 3) * g_Task->unk_09;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), 128U);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), 128U);
    for (i = 1; i <= 16; i++) {
        GFX_STEP_TRIANGLE_FAN(i << 8, 128U);
        prim                      = (POLY_G3*)g_GfxPrimCursor;
        g_ScratchPadVectors[2].vz = 0;
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EF934(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), 128U);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), 128U);
    g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(0), 256U);
    g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0), 256U);
    for (i = 1; i <= 16; i++) {
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 8), 128U);
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 8), 128U);
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 8), 256U);
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 8), 256U);
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

MATCH void func_801EFBBC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Task);
}

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

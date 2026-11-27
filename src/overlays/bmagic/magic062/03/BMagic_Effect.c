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

    actor                           = g_Battle.selected_actor;
    SELF(PartyMember)->facing       = actor->facing;
    SELF(PartyMember)->pos.x.fixed  = actor->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed  = actor->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed  = actor->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 16;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 74);
    owner                              = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0;
    g_BattleEffects[slot].target.party = owner;
    g_BattleEffects[slot].pos.x.fixed  = SELF(PartyMember)->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = SELF(PartyMember)->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = SELF(PartyMember)->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B += 1;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 74);
        spawner                            = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i * 8;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
        g_BattleEffects[slot].target.party = spawner;
        g_BattleEffects[slot].unk_0A       = SELF(PartyMember)->unk_09;
        SELF(PartyMember)->param.unk_0B += 1;
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

    g_PaletteFades[SELF(PartyMember)->timer].offset.r--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b--;
    if (--SELF(PartyMember)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        for (i = 0; i < 4; i++) {
            func_801EF2F0(D_800B6BF0[i]);
            slot                               = Battle_AllocEffect(1, 72);
            owner                              = SELF(PartyMember);
            g_BattleEffects[slot].unk_04       = i;
            g_BattleEffects[slot].arg.unk_09   = i * 5 + 1;
            g_BattleEffects[slot].unk_0A       = i * 12 + 1;
            g_BattleEffects[slot].target.party = owner;
            SELF(PartyMember)->param.unk_0B++;
        }
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EF2A0(void) {
    u16* flags;

    if (SELF(PartyMember)->param.unk_0B == 0) {
        flags                     = &g_Battle.flags;
        g_GameCelerityTimer.hours = 5;
        *flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

MATCH void func_801EF2F0(s32 stat) {
    s16 change;
    s32 delta;

    if (g_Battle.target_selector < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Battle.target_record = &g_Game.members[g_Battle.target_selector].u.turn;
    } else {
        g_Battle.target_record = &ENEMY_COMBATANT(g_Battle.target_selector).turn;
    }
    g_Battle.target_record->hp_change    = 0;
    g_Battle.target_record->ap_change    = 0;
    g_Battle.target_record->target_flags = 0;
    change                               = (s8)g_Abilities[g_Battle.action_id].power;
    delta                                = ((s8*)g_Battle.target_record + (u8)stat)[0x14] + change;
    if (delta > 100) {
        ((s8*)g_Battle.target_record + (u8)stat)[0x14] = 100;
    } else if (delta < -100) {
        ((s8*)g_Battle.target_record + (u8)stat)[0x14] = -100;
    } else {
        ((s8*)g_Battle.target_record + (u8)stat)[0x14] += change;
        Battle_RescaleStats(g_Battle.target_selector);
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF4C4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF508(void) {
    SYS_DISPATCH_BYTE(D_801F0C18, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
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
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 * 5;
    g_ScratchPad.cells.halves[4] = ((rand() & 3) + 3) * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = ((rand() & 3) + 3) * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = ((rand() & 3) + 3) * SELF(PartyMember)->unk_09;
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
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Self);
}

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

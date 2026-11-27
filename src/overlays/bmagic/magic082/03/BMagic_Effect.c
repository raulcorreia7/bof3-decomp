#include "magic082_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    u8           i;
    u8           slot;
    PartyMember* actor;
    u16*         dst;
    u16*         src;

    actor                     = g_Battle.selected_actor;
    SELF(PartyMember)->facing = actor->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &actor->pos);
    SELF(PartyMember)->unk_04       = func_801EF3A0();
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 16;
    SELF(PartyMember)->header.mode += 1;
    slot = Battle_AllocEffect(1, 5);
    {
        PartyMember* work;

        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = SELF(PartyMember)->unk_04;
        g_BattleEffects[slot].arg.unk_09   = 0;
    }
    {
        PartyMember* work;

        work                        = SELF(PartyMember);
        g_BattleEffects[slot].pos.x = work->pos.x;
        g_BattleEffects[slot].pos.y = work->pos.y;
        g_BattleEffects[slot].pos.z = work->pos.z;
        work->param.unk_0B += 1;
    }
    for (i = 0; i < 4; i++) {
        PartyMember* work;

        slot                               = Battle_AllocEffect(1, 5);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].unk_04       = SELF(PartyMember)->unk_04;
        g_BattleEffects[slot].unk_0B       = i * 8;
        g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
        g_BattleEffects[slot].unk_0A       = SELF(PartyMember)->unk_09;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

#include "overlays/bmagic/shared/Effect_ReplacePaletteFade.h"

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

/* func_801EF0C4 */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(2);
}

MATCH void func_801EF10C(void) {
    u8  timer;
    u32 slot;

    g_PaletteFades[SELF(PartyMember)->timer].offset.r--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b--;
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        if (Battle_CanTarget(D_800B6BF0[SELF(PartyMember)->unk_04], g_Battle.target_selector) & BYTE_MASK) {
            slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
            g_BattleEffects[slot].target.party = SELF(PartyMember);
            g_BattleEffects[slot].unk_04       = SELF(PartyMember)->unk_04;
            g_BattleEffects[slot].arg.unk_09   = 1;
            g_BattleEffects[slot].unk_0A       = 0;
            SELF(PartyMember)->param.unk_0B++;
        } else {
            slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
            g_BattleEffects[slot].target.party = SELF(PartyMember);
            g_BattleEffects[slot].unk_04       = 8;
            g_BattleEffects[slot].arg.unk_09   = 1;
            g_BattleEffects[slot].unk_0A       = 0;
            SELF(PartyMember)->param.unk_0B++;
        }
        SELF(PartyMember)->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

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

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF56C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF5B0(void) {
    SYS_DISPATCH_BYTE(D_801F0D1C, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EFA00();
        func_801EF720();
        PopMatrix();
    }
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

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
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 * 5;
    g_ScratchPad.cells.halves[4] = D_801F0CFC[SELF(PartyMember)->unk_04][0] * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = D_801F0CFC[SELF(PartyMember)->unk_04][1] * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = D_801F0CFC[SELF(PartyMember)->unk_04][2] * SELF(PartyMember)->unk_09;
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
    g_ScratchPad.cells.halves[4] = D_801F0D08[SELF(PartyMember)->unk_04][0] * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = D_801F0D08[SELF(PartyMember)->unk_04][1] * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = D_801F0D08[SELF(PartyMember)->unk_04][2] * SELF(PartyMember)->unk_09;
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
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Self);
}

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

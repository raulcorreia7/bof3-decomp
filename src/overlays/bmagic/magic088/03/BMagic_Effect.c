#include "magic088_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC20.h"

MATCH void func_801EECA4(void) {
    PartyMember* actor;
    u8           slot;
    u8           i;
    u16*         src;
    u16*         dst;

    actor                           = g_Battle.selected_actor;
    TASK(PartyMember)->pos.x.fixed  = actor->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = actor->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = actor->pos.z.fixed;
    TASK(PartyMember)->unk_04       = func_801EF34C();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 16;
    TASK(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 32);
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0;
    g_BattleEffects[slot].unk_0A       = 0;
    g_BattleEffects[slot].pos.x.fixed  = TASK(PartyMember)->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = TASK(PartyMember)->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = TASK(PartyMember)->pos.z.fixed;
    TASK(PartyMember)->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 32);
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].unk_04       = TASK(PartyMember)->unk_04;
    g_BattleEffects[slot].arg.unk_09   = TASK(PartyMember)->unk_09;
    g_BattleEffects[slot].unk_0A       = 16;
    g_BattleEffects[slot].pos.x.fixed  = TASK(PartyMember)->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = TASK(PartyMember)->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = TASK(PartyMember)->pos.z.fixed;
    TASK(PartyMember)->param.unk_0B += 1;
    for (i = 0, dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors, src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEEF4(void) {
    PartyMember* battler;
    u8           value;

    battler                   = g_Battle.selected_actor;
    value                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        battler->unk_5C = 1;
        GFX_PaletteFreeFadeTarget(battler);
        TASK(PartyMember)->timer  = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEFA0(void) {
    u8 timer;

    g_PaletteFades[TASK(PartyMember)->timer].offset.r--;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g--;
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_Pause.h"

MATCH void func_801EF0A8(void) {
    PartyMember* actor;

    actor = g_Battle.selected_actor;
    g_PaletteFades[TASK(PartyMember)->timer].offset.r++;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g++;
    if (g_PaletteFades[TASK(PartyMember)->timer].offset.r != 0) {
        return;
    }
    actor->unk_5C = 0;
    func_80196718(actor);
    Battle_FadePoisonedBattler(g_Battle.target_selector);
    TASK(PartyMember)->header.mode += 1;
}

MATCH void func_801EF1AC(void) {
    u32 slot;

    if (TASK(PartyMember)->param.unk_0B != 0) {
        return;
    }
    if (Battle_CanTarget(D_800B6BF0[TASK(PartyMember)->unk_04], g_Battle.target_selector) & BYTE_MASK) {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].unk_04       = TASK(PartyMember)->unk_04 + 4;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        TASK(PartyMember)->param.unk_0B++;
    } else {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].unk_04       = 8;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        TASK(PartyMember)->param.unk_0B++;
    }
    TASK(PartyMember)->header.mode++;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF34C(void) {
    s32 result;

    if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_Battle.action_id)) {
            case ABILITY_WEAKEN:
            case ABILITY_WEAKEN_SKILL:
                result = 0;
                break;
            case ABILITY_MOLASSES:
            case ABILITY_SLOW:
            case ABILITY_SLOW_SKILL:
                result = 1;
                break;
            case ABILITY_TARBABY:
            case ABILITY_BLUNT:
            case ABILITY_BLUNT_SKILL:
                result = 2;
                break;
            default:
                result = 3;
                break;
        }
    } else if (LOHU(g_Battle.action_id) == 0x112) {
        g_Battle.action_id = ABILITY_WEAKEN;
        result             = 0;
    } else {
        result = 3;
    }
    return result;
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF4E0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF524(void) {
    SYS_DISPATCH_BYTE(D_801F0030, TASK(PartyMember)->header.step);
    BMAGIC_DRAW_IF_ALIVE(func_801EF68C);
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801EF68C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09 * 12;
    g_ScratchPad.cells.halves[0] = 240;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
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
        setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EF900(void) {
    SYS_DISPATCH_BYTE(D_801F005C, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFAE8();
        func_801EFB34();
        PopMatrix();
    }
}

#include "overlays/bmagic/shared/Effect_CountDownTimerStep.h"

#include "overlays/bmagic/shared/Effect_CountUpAndStepAt32.h"

MATCH void func_801EFA2C(void) {
    u8 timer_next;

    timer_next               = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFA94(void) {
    PartyMember* work;

    work         = TASK(PartyMember);
    work->unk_09 = work->unk_09 - 2;
    if (TASK(PartyMember)->unk_09 == 0) {
        Effect_Reset();
    }
}

MATCH void func_801EFAE8(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (i & 0x1) {
            D_801F003C[i] = D_801F003C[i] - 1;
        } else {
            D_801F003C[i] = D_801F003C[i] + 1;
        }
    }
}

MATCH void func_801EFB34(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      band;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->unk_09;
    for (band = 0; band < 6; band++) {
        g_ScratchPad.cells.halves[0] = band << 5;
        g_ScratchPad.cells.halves[1] = (band + 1) << 5;
        g_ScratchPad.cells.halves[5] = D_801EFFE0[TASK(PartyMember)->unk_04][band][0] * (TASK(PartyMember)->unk_09 >> 1);
        g_ScratchPad.cells.halves[6] = D_801EFFE0[TASK(PartyMember)->unk_04][band][1] * (TASK(PartyMember)->unk_09 >> 1);
        g_ScratchPad.cells.halves[7] = D_801EFFE0[TASK(PartyMember)->unk_04][band][2] * (TASK(PartyMember)->unk_09 >> 1);
        g_ScratchPad.cells.halves[3] = (D_801F003C[band] & 0xF) << 8;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[1].vz    = -(g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[4]));
        g_ScratchPad.cells.halves[3] = ((D_801F003C[band] + 1) & 0xF) << 8;
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[3].vz    = -(g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[4]));
        for (i = 1; i <= 64; i++) {
            g_ScratchPad.cells.halves[2] = i << 6;
            g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[0].vz    = g_ScratchPadVectors[1].vz;
            setVector(&g_ScratchPadVectors[2], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, g_ScratchPadVectors[3].vz);
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]), FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]),
                      -(g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[4])));
            g_ScratchPad.cells.halves[3] = ((i + D_801F003C[band] + 1) & 0xF) << 8;
            setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
                      -(g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[4])));
            prim = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
            Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_F4));
        }
    }
}

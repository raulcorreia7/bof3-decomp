#include "magic137_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EEC7C(void) {
    u16*             dst;
    u16*             src;
    s32              index;
    u32              i;
    u32              enemy;
    BattleEffect*    effect;
    BattleWorkImage* image;

    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0x18;
    TASK(PartyMember)->header.mode += 1;
    index                               = (u8)Battle_AllocEffect(1, 0x4B);
    g_BattleEffects[index].target.party = g_Task;
    g_BattleEffects[index].header.mode  = 0;
    g_BattleEffects[index].unk_08       = g_BattleEffectBattler->facing;

    TASK(PartyMember)->param.unk_0B += 1;
    index                               = (u8)Battle_AllocEffect(1, 0x4B);
    g_BattleEffects[index].target.party = g_Task;
    g_BattleEffects[index].header.mode  = 1;

    TASK(PartyMember)->param.unk_0B += 1;
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    g_GfxPalettePending = 1;
    if (g_Battle.encounter != 0) {
        if (g_BattleEnemyBattlers[g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT].unk_F0 == 0x29) {
            index                              = (u8)Battle_AllocEffect(1, 0x4B);
            enemy                              = g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT;
            effect                             = &g_BattleEffects[index];
            image                              = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
            *(BattleWorkImage*)effect          = *image;
            g_BattleEffects[index].header.mode = 2;
            g_BattleEffects[index].unk_06      = 1;
            g_BattleEffects[index].effect_type = 0x4B;
            g_BattleEffects[index].header.step = 0;
            g_BattleEffects[index].arg.unk_09  = 0;
            g_BattleEffects[index].unk_29      = 3;
        }
    }
}
#else
INCLUDE_ASM(func_801EEC7C);
#endif

#include "overlays/bmagic/shared/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEF64(void) {
    if (TASK(PartyMember)->param.phase == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        TASK(PartyMember)->unk_09 = 30;
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EEFD4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF018(void) {
    SYS_DISPATCH_BYTE(D_801F0104, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Effect_SetFacingMatrix();
        func_801EF4C4();
        PopMatrix();
    }
}

MATCH void func_801EF090(void) {
    PartyMember* work;

    TASK(PartyMember)->unk_0C = -TO_COORD_HALF(2);
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    TASK(PartyMember)->pos.x.fixed        = g_AreaScrollTargetCoordX.fixed + TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed        = g_AreaScrollTargetCoordY.fixed + TASK(PartyMember)->unk_10;
    TASK(PartyMember)->pos.z.part.integer = Area_HeightSample(g_AreaScrollTargetCoordX.fixed, g_AreaScrollTargetCoordY.fixed) + 0x200;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    work                      = TASK(PartyMember);
    work->param.unk_0B        = 0x34;
    work->unk_14              = 0x2FFF;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->timer  = 0x10;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF174(void) {
    PartyMember* work = TASK(PartyMember);
    u8           count;
    u8           phase = work->param.phase;
    u8           timer;
    phase += 1;
    timer             = work->unk_09;
    work->param.phase = phase + (timer >> 6);
    if (g_FrameCount & 0x1) {
        TASK(PartyMember)->timer += 1;
    }
    count                     = TASK(PartyMember)->unk_09 + 2;
    TASK(PartyMember)->unk_09 = count;
    if (count == 192) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF21C(void) {
    PartyMember* work = TASK(PartyMember);
    u8           count;
    u8           phase = work->param.phase;
    u8           timer;
    phase += 1;
    timer             = work->unk_09;
    work->param.phase = phase + (timer >> 6);
    if (g_FrameCount & 0x1) {
        TASK(PartyMember)->timer -= 1;
    }
    count                     = TASK(PartyMember)->unk_09 - 2;
    TASK(PartyMember)->unk_09 = count;
    if (count == 96) {
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_Drift.h"

#include "overlays/bmagic/shared/Effect_SetFacingMatrix.h"

MATCH void func_801EF4C4(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    g_ScratchPad.cells.halves[1] = 128;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[2] = 128;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->timer;
    g_ScratchPad.cells.halves[4] = (TASK(PartyMember)->param.unk_0B & 0x3F) << 6;
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(0x580), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0x580), g_ScratchPad.cells.halves[2]),
              FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0x280), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0x280), g_ScratchPad.cells.halves[2]),
              FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    for (i = 1; i < g_ScratchPad.cells.halves[0]; i++) {
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (i << 5) + 128;
        g_ScratchPad.cells.halves[4] = ((TASK(PartyMember)->param.unk_0B + i) & 0x3F) << 6;
        g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[2].vz    = g_ScratchPadVectors[0].vz;
        g_ScratchPadVectors[3].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[3].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[3].vz    = g_ScratchPadVectors[1].vz;
        setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(0x580), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0x580), g_ScratchPad.cells.halves[2]),
                  FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0x280), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0x280), g_ScratchPad.cells.halves[2]),
                  FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
        if (TASK(PartyMember)->header.step == 3) {
            g_ScratchPad.cells.halves[1] = (TASK(PartyMember)->unk_09 - 48) / 3 * 8;
        }
        GFX_SET_RGB_ALL(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        if (i < 16) {
            setRGB0(prim, g_ScratchPad.cells.halves[1] / 16 * (i + 1), g_ScratchPad.cells.halves[1] / 16 * (i + 1), g_ScratchPad.cells.halves[1] / 16 * (i + 1));
            setRGB1(prim, prim->r0, prim->g0, prim->b0);
            setRGB2(prim, g_ScratchPad.cells.halves[1] / 16 * i, g_ScratchPad.cells.halves[1] / 16 * i, g_ScratchPad.cells.halves[1] / 16 * i);
            setRGB3(prim, prim->r2, prim->g2, prim->b2);
        }
        if (g_ScratchPad.cells.halves[0] - 8 < i) {
            g_ScratchPad.cells.halves[5] = g_ScratchPad.cells.halves[1];
            g_ScratchPad.cells.halves[1] = g_ScratchPad.cells.halves[1] / 8 * (g_ScratchPad.cells.halves[0] - i);
            setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
            setRGB1(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
            g_ScratchPad.cells.halves[1] = g_ScratchPad.cells.halves[5] / 8 * (g_ScratchPad.cells.halves[0] - (i - 1));
            setRGB2(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
            setRGB3(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        }
        prim->tpage                  = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 832, 256);
        prim->clut                   = GetClut(0, 506);
        g_ScratchPad.cells.halves[7] = 252 - ((((g_FrameCount * 2) ^ 0xFFFF) + i) & 0x3F) * 4;
        if (g_ScratchPad.cells.halves[7] == 252) {
            g_ScratchPad.cells.halves[7] = 251;
        }
        setUV4(prim, 0, g_ScratchPad.cells.halves[7], 255, g_ScratchPad.cells.halves[7], 0, g_ScratchPad.cells.halves[7] + 4, 255, g_ScratchPad.cells.halves[7] + 4);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_GT4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

MATCH void func_801EFC58(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 2, g_Task);
    if (TASK(PartyMember)->header.flags != 0) {
        func_801EFDF8();
    }
}

#include "overlays/bmagic/shared/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801EFDF8(void) {
    POLY_G4* prim;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (g_BattleEffectBattler->facing & 1) {
        setXYWH(prim, 0, 0, 319, 239);
    } else {
        setXY4(prim, 0x13F, 0, 0, 0, 0x13F, 0xEF, 0, 0xEF);
    }
    prim->r0 = prim->r3 = prim->g0 = prim->g3 = prim->b0 = prim->b3 = TASK(PartyMember)->unk_09;
    prim->r1 = prim->r2 = TASK(PartyMember)->unk_09 * 12;
    prim->g1 = prim->b1 = prim->g2 = prim->b2 = TASK(PartyMember)->unk_09 * 4;
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

#include "overlays/bmagic/shared/Effect_DispatchStep.h"

MATCH void func_801F001C(void) {
    TASK(PartyMember)->param.phase = 0;
    TASK(PartyMember)->unk_09      = 0;
    Script_Select(3);
    Script_AnimStepLoop();
    Area_AddActor();
    TASK(PartyMember)->header.step++;
}

#include "overlays/bmagic/shared/Effect_AddActor.h"

MATCH void func_801F00D8(void) {
    Effect_Reset();
}

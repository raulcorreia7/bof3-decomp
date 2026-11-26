#include "magic067_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    Magic067Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EEC94(void) {
    BattleEffect*    effect;
    BattleWorkImage* image;
    PartyMember*     work;
    u32              slot;
    u32              enemy;
    u16*             src;
    u16*             dst;
    u32              i;

    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0x18;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 0x13) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].unk_08       = g_BattleEffectBattler->facing;
    SELF(PartyMember)->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 0x13) & BYTE_MASK;
    work                               = g_Self;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = work;
    SELF(PartyMember)->param.unk_0B += 1;
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BMAGIC_ROW));
    src = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BMAGIC_ROW));
    for (; i < 0x100; i++) {
        dst[i] = src[i] | PSX_COLOR_STP_BIT;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 0x10; i++) {
        dst[0]    = src[0];
        dst[0x10] = src[0x10];
        dst++;
        src++;
    }
    g_GfxPalettePending = 1;
    if (g_Battle.encounter != 0) {
        if (g_BattleEnemyBattlers[g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT].unk_F0 == 0x29) {
            slot                              = Battle_AllocEffect(1, 0x13) & BYTE_MASK;
            enemy                             = g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT;
            effect                            = &g_BattleEffects[slot];
            image                             = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
            *(BattleWorkImage*)effect         = *image;
            g_BattleEffects[slot].header.mode = 3;
            g_BattleEffects[slot].unk_06      = 1;
            g_BattleEffects[slot].header.step = 0;
            g_BattleEffects[slot].effect_type = 0x13;
            g_BattleEffects[slot].arg.unk_09  = 0;
        }
    }
}
#else
INCLUDE_ASM(func_801EEC94);
#endif

#include "overlays/bmagic/shared/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEFA4(void) {
    if (SELF(PartyMember)->param.phase == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        SELF(PartyMember)->unk_09 = 0x1E;
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF010(void) {
    u8 slot;
    u8 count;
    u8 battler;
    u8 i;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        if (g_Battle.target_selector & 0x40) {
            for (i = 0; i < 8; i++) {
                battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
                if (!Battle_SlotIsBlocked(battler)) {
                    slot                               = Battle_AllocEffect(1, 0x13);
                    g_BattleEffects[slot].target.party = SELF(PartyMember);
                    g_BattleEffects[slot].header.mode  = 2;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].unk_04       = 5;
                    g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                    g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                    g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;
                    SELF(PartyMember)->param.unk_0B += 1;
                }
            }
        } else {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!Battle_SlotIsBlocked(i)) {
                    slot                               = Battle_AllocEffect(1, 0x13);
                    g_BattleEffects[slot].target.party = SELF(PartyMember);
                    g_BattleEffects[slot].header.mode  = 2;
                    g_BattleEffects[slot].unk_04       = 5;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                    g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                    g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;
                    SELF(PartyMember)->param.unk_0B += 1;
                }
            }
        }
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EF2D0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF314(void) {
    SYS_DISPATCH_BYTE(D_801F04C8, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Effect_SetFacingMatrix();
        func_801EF79C();
        PopMatrix();
    }
}

MATCH void func_801EF38C(void) {
    PartyMember* work;

    func_800AFD9C();
    SELF(PartyMember)->unk_0C = -0x40000;
    SELF(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->pos.x.fixed = g_AreaScrollTargetCoordX.fixed + SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed = g_AreaScrollTargetCoordY.fixed + SELF(PartyMember)->unk_10;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    work                      = SELF(PartyMember);
    work->param.unk_0B        = 0x34;
    work->unk_14              = 0x2FFF;
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = 0x10;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF44C(void) {
    s32 count;
    u8  count_next;

    count = SELF(PartyMember)->param.phase + 1;
    count += SELF(PartyMember)->unk_09 >> 6;
    SELF(PartyMember)->param.phase = count;
    if (g_FrameCount & 0x1) {
        SELF(PartyMember)->timer += 1;
    }
    count_next                = SELF(PartyMember)->unk_09 + 2;
    SELF(PartyMember)->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0xC0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF4F4(void) {
    s32 count;
    u8  count_next;

    count = SELF(PartyMember)->param.phase + 1;
    count += SELF(PartyMember)->unk_09 >> 6;
    SELF(PartyMember)->param.phase = count;
    if (g_FrameCount & 0x1) {
        SELF(PartyMember)->timer -= 1;
    }
    count_next                = SELF(PartyMember)->unk_09 - 2;
    SELF(PartyMember)->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0x60) {
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_Drift.h"

#include "overlays/bmagic/shared/Effect_SetFacingMatrix.h"

MATCH void func_801EF79C(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    g_ScratchPad.cells.halves[1] = 128;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[2] = 512;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[4] = (SELF(PartyMember)->param.unk_0B & 0x3F) << 6;
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rsin(0x580), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0x580), g_ScratchPad.cells.halves[2]),
              FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0x280), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0x280), g_ScratchPad.cells.halves[2]),
              FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]));
    for (i = 1; i < g_ScratchPad.cells.halves[0]; i++) {
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (i << 5) + 512;
        g_ScratchPad.cells.halves[4] = ((SELF(PartyMember)->param.unk_0B + i) & 0x3F) << 6;
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
        if (SELF(PartyMember)->header.step == 3) {
            g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->unk_09 - 48) / 3 * 8;
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
        prim->clut                   = GetClut(0, 482);
        g_ScratchPad.cells.halves[7] = 252 - ((((g_FrameCount * 2) ^ 0xFFFF) + i) & 0x3F) * 3;
        setUV4(prim, 0, g_ScratchPad.cells.halves[7], 255, g_ScratchPad.cells.halves[7], 0, g_ScratchPad.cells.halves[7] + 3, 255, g_ScratchPad.cells.halves[7] + 3);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_GT4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

MATCH void func_801EFF24(void) {
    D_801F04D8[SELF(PartyMember)->header.step]();
    if (SELF(PartyMember)->header.flags != 0) {
        func_801F00C4();
    }
}

#include "overlays/bmagic/shared/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801F00C4(void) {
    POLY_G4* prim;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (g_BattleEffectBattler->facing & 1) {
        setXYWH(prim, 0, 0, 319, 239);
    } else {
        setXY4(prim, 319, 0, 0, 0, 319, 239, 0, 239);
    }
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_09 * 8;
    setRGB0(prim, prim->r3 = g_ScratchPad.cells.halves[0], prim->g3 = g_ScratchPad.cells.halves[0], prim->b3 = g_ScratchPad.cells.halves[0]);
    setRGB1(prim, prim->r2 = g_ScratchPad.cells.halves[1], prim->g2 = g_ScratchPad.cells.halves[1], prim->b2 = g_ScratchPad.cells.halves[1]);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

MATCH void func_801F02A0(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 12, 2, g_Self);
}

#include "overlays/bmagic/shared/Effect_QueueEntry.h"

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"

MATCH void func_801F038C(void) {
    Magic067SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
}

MATCH void func_801F03EC(void) {
    SELF(PartyMember)->param.phase = 0;
    SELF(PartyMember)->unk_09      = 0;
    Script_Select(3);
    SELF(PartyMember)->header.step++;
}

#include "overlays/bmagic/shared/Effect_AddActor.h"

MATCH void func_801F0498(void) {
    Effect_Reset();
}

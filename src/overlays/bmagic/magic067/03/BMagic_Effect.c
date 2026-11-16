#include "magic067_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    Magic067Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EEC94(void) {
    u32  slot;
    u16* src;
    u16* dst;
    u32  i;

    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0x18;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 0x13) & BYTE_MASK;
    g_BattleEffects[slot].target.party = (PartyMember*)g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].unk_08       = g_BattleEffectBattler->facing;
    g_Task->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 0x13) & BYTE_MASK;
    i                                  = 0;
    dst                                = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    src                                = MEM_PTR(u16, AREA_PALETTE_ARENA + 2 * AREA_PALETTE_ROW);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = (PartyMember*)g_Task;
    g_Task->param.unk_0B += 1;
    for (; i < 0x100; i++) {
        *dst++ = *src++ | 0x8000;
    }
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (i = 0; i < 0x10; i++) {
        dst[0]    = src[0];
        dst[0x10] = src[0x10];
        dst++;
        src++;
    }
    g_GfxPalettePending = 1;
    if (g_Battle.encounter != 0 && g_BattleEnemyBattlers[g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT].unk_F0 == 0x29) {
        slot = Battle_AllocEffect(1, 0x13) & BYTE_MASK;
        memcpy(&g_BattleEffects[slot], &g_BattleEnemyBattlers[g_Battle.active_battler - BATTLE_PARTY_CHARACTERS_COUNT], 0x74);
        g_BattleEffects[slot].header.mode   = 3;
        g_BattleEffects[slot].unk_06        = 1;
        g_BattleEffects[slot].header.step   = 0;
        g_BattleEffects[slot].handler_index = 0x13;
        g_BattleEffects[slot].arg.unk_09    = 0;
    }
}
#else
INCLUDE_ASM(func_801EEC94);
#endif

#include "overlays/bmagic/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEFA4(void) {
    if (g_Task->param.phase == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 0x1E;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF010(void) {
    u8 slot;
    u8 count;
    u8 battler;
    u8 i;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        if (g_Battle.target_selector & 0x40) {
            for (i = 0; i < 8; i++) {
                battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
                if (!Battle_SlotIsBlocked(battler)) {
                    slot                               = Battle_AllocEffect(1, 0x13);
                    g_BattleEffects[slot].target.party = g_Task;
                    g_BattleEffects[slot].header.mode  = 2;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].unk_04       = 5;
                    g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                    g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                    g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;
                    g_Task->param.unk_0B += 1;
                }
            }
        } else {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!Battle_SlotIsBlocked(i)) {
                    slot                               = Battle_AllocEffect(1, 0x13);
                    g_BattleEffects[slot].target.party = g_Task;
                    g_BattleEffects[slot].header.mode  = 2;
                    g_BattleEffects[slot].unk_04       = 5;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                    g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                    g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;
                    g_Task->param.unk_0B += 1;
                }
            }
        }
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF2D0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF314(void) {
    SYS_DISPATCH_BYTE(D_801F04C8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetFacingMatrix();
        func_801EF79C();
        PopMatrix();
    }
}

MATCH void func_801EF38C(void) {
    PartyMember* work;

    func_800AFD9C();
    g_Task->unk_0C = -0x40000;
    g_Task->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    /* FAKE: the cast store keeps the y read behind the x store. */
    LOW(g_Task->pos.x.fixed) = g_AreaScrollTargetX + g_Task->unk_0C;
    g_Task->pos.y.fixed      = g_AreaScrollTargetY + g_Task->unk_10;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    work               = g_Task;
    work->param.unk_0B = 0x34;
    work->unk_14       = 0x2FFF;
    g_Task->unk_09     = 0;
    g_Task->timer      = 0x10;
    g_Task->header.step += 1;
}

MATCH void func_801EF44C(void) {
    s32 count;
    u8  count_next;

    count = g_Task->param.phase + 1;
    count += g_Task->unk_09 >> 6;
    g_Task->param.phase = count;
    if (g_FrameCount & 0x1) {
        g_Task->timer += 1;
    }
    count_next     = g_Task->unk_09 + 2;
    g_Task->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0xC0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4F4(void) {
    s32 count;
    u8  count_next;

    count = g_Task->param.phase + 1;
    count += g_Task->unk_09 >> 6;
    g_Task->param.phase = count;
    if (g_FrameCount & 0x1) {
        g_Task->timer -= 1;
    }
    count_next     = g_Task->unk_09 - 2;
    g_Task->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0x60) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_Drift.h"

#include "overlays/bmagic/Effect_SetFacingMatrix.h"

MATCH void func_801EF79C(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;

    tpage = getTPage(1, 1, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(2, tpage);
    D_1F800000.cells.halves[1] = 128;
    D_1F800000.cells.halves[0] = g_Task->unk_09;
    D_1F800000.cells.halves[2] = 512;
    D_1F800000.cells.halves[3] = g_Task->timer;
    D_1F800000.cells.halves[4] = (g_Task->param.unk_0B & 0x3F) << 6;
    setVector(&D_1F800014[0], FIXED_MUL(rsin(0x580), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x580), D_1F800000.cells.halves[2]),
              FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
    setVector(&D_1F800014[1], FIXED_MUL(rsin(0x280), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x280), D_1F800000.cells.halves[2]),
              FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
    for (i = 1; i < D_1F800000.cells.halves[0]; i++) {
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.cells.halves[2] = (i << 5) + 512;
        D_1F800000.cells.halves[4] = ((g_Task->param.unk_0B + i) & 0x3F) << 6;
        D_1F800014[2].vx           = D_1F800014[0].vx;
        D_1F800014[2].vy           = D_1F800014[0].vy;
        D_1F800014[2].vz           = D_1F800014[0].vz;
        D_1F800014[3].vx           = D_1F800014[1].vx;
        D_1F800014[3].vy           = D_1F800014[1].vy;
        D_1F800014[3].vz           = D_1F800014[1].vz;
        setVector(&D_1F800014[0], FIXED_MUL(rsin(0x580), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x580), D_1F800000.cells.halves[2]),
                  FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
        setVector(&D_1F800014[1], FIXED_MUL(rsin(0x280), D_1F800000.cells.halves[2]), FIXED_MUL(rcos(0x280), D_1F800000.cells.halves[2]),
                  FIXED_MUL(rsin(D_1F800000.cells.halves[4]), D_1F800000.cells.halves[3]));
        if (g_Task->header.step == 3) {
            D_1F800000.cells.halves[1] = (g_Task->unk_09 - 48) / 3 * 8;
        }
        setRGB0(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
        setRGB1(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
        setRGB2(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
        setRGB3(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
        if (i < 16) {
            setRGB0(prim, D_1F800000.cells.halves[1] / 16 * (i + 1), D_1F800000.cells.halves[1] / 16 * (i + 1), D_1F800000.cells.halves[1] / 16 * (i + 1));
            setRGB1(prim, prim->r0, prim->g0, prim->b0);
            setRGB2(prim, D_1F800000.cells.halves[1] / 16 * i, D_1F800000.cells.halves[1] / 16 * i, D_1F800000.cells.halves[1] / 16 * i);
            setRGB3(prim, prim->r2, prim->g2, prim->b2);
        }
        if (D_1F800000.cells.halves[0] - 8 < i) {
            D_1F800000.cells.halves[5] = D_1F800000.cells.halves[1];
            D_1F800000.cells.halves[1] = D_1F800000.cells.halves[1] / 8 * (D_1F800000.cells.halves[0] - i);
            setRGB0(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
            setRGB1(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
            D_1F800000.cells.halves[1] = D_1F800000.cells.halves[5] / 8 * (D_1F800000.cells.halves[0] - (i - 1));
            setRGB2(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
            setRGB3(prim, D_1F800000.cells.halves[1], D_1F800000.cells.halves[1], D_1F800000.cells.halves[1]);
        }
        prim->tpage                = GetTPage(1, 1, 832, 256);
        prim->clut                 = GetClut(0, 482);
        D_1F800000.cells.halves[7] = 252 - ((((g_FrameCount * 2) ^ 0xFFFF) + i) & 0x3F) * 3;
        setUV4(prim, 0, D_1F800000.cells.halves[7], 255, D_1F800000.cells.halves[7], 0, D_1F800000.cells.halves[7] + 3, 255, D_1F800000.cells.halves[7] + 3);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(2, sizeof(POLY_GT4));
    }
    tpage = getTPage(0, 0, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(2, tpage);
}

MATCH void func_801EFF24(void) {
    D_801F04D8[g_Task->header.step]();
    if (g_Task->header.flags != 0) {
        func_801F00C4();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801F00C4(void) {
    POLY_G4* prim;

    GFX_AddDitheredDrawMode(2, getTPage(0, 1, 320, 256));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (g_BattleEffectBattler->facing & 1) {
        setXYWH(prim, 0, 0, 319, 239);
    } else {
        setXY4(prim, 319, 0, 0, 0, 319, 239, 0, 239);
    }
    D_1F800000.cells.halves[0] = g_Task->unk_09;
    D_1F800000.cells.halves[1] = g_Task->unk_09 * 8;
    setRGB0(prim, prim->r3 = D_1F800000.cells.halves[0], prim->g3 = D_1F800000.cells.halves[0], prim->b3 = D_1F800000.cells.halves[0]);
    setRGB1(prim, prim->r2 = D_1F800000.cells.halves[1], prim->g2 = D_1F800000.cells.halves[1], prim->b2 = D_1F800000.cells.halves[1]);
    GFX_AddPrim(2, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(2, getTPage(0, 0, 320, 256));
}

MATCH void func_801F02A0(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 12, 2, g_Task);
}

#include "overlays/bmagic/Effect_QueueEntry.h"

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801F038C(void) {
    Magic067SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801F03EC(void) {
    g_Task->param.phase = 0;
    g_Task->unk_09      = 0;
    Actor_SelectScript(3);
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_AddActor.h"

MATCH void func_801F0498(void) {
    Effect_Reset();
}

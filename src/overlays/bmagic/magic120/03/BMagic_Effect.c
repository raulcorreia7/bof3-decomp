#include "magic120_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    u32          slot;
    u32          i;
    PartyMember* work;
    PartyMember* battler;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    slot                               = Battle_AllocEffect(1, 15) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 4;
    g_BattleEffects[slot].target.party = work;
    slot                               = Battle_AllocEffect(1, 15) & BYTE_MASK;
    battler                            = g_BattleEffectBattler;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].unk_0B       = 0;
    g_BattleEffects[slot].target.party = battler;
    if (!(g_Task->facing & 2)) {
        PartyMember* owner;

        slot                               = Battle_AllocEffect(1, 15) & BYTE_MASK;
        owner                              = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = 1;
        g_BattleEffects[slot].target.party = owner;
    }
    {
        u16* row;
        u16* arena;

        for (i = 1, row = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) + 1, arena = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW) + 1; i < 16; i++) {
            *row++ = *arena++ | 0x8000;
        }
    }
    {
        u16* arena;
        u16* row;

        for (i = 1, arena = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW) + 1, row = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) + 1; i < 16; i++) {
            row[16] = arena[16];
            arena++;
            row++;
        }
    }
    {
        u16* arena;
        u16* row;

        for (i = 1, arena = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW) + 1, row = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) + 1; i < 16; i++) {
            row[32] = arena[32] | 0x8000;
            arena++;
            row++;
        }
    }
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[0]  = 0;
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[16] = 0;
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[32] = 0;
    g_GfxPalettePending                                         = 1;
    g_Task->param.unk_0B                                        = 0;
    g_Task->unk_09                                              = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEEC8(void) {
    u32          slot;
    PartyMember* task;
    PartyMember* task2;

    if (g_Task->param.unk_0B == 1) {
        slot                               = Battle_AllocEffect(1, 15) & BYTE_MASK;
        task                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = 2;
        g_BattleEffects[slot].target.party = task;
        slot                               = Battle_AllocEffect(1, 15) & BYTE_MASK;
        task2                              = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = 3;
        g_BattleEffects[slot].target.party = task2;
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

/* func_801EF010 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

/* func_801EF054 */
MATCH void BMagic_UpdateWhelpBreath(void) {
    SYS_DISPATCH_BYTE(D_801F0CB0, g_Task->header.step);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        if (g_Task->header.step != 0) {
            BMagic_DrawWhelpBreath();
        }
    }
}

/* Projects the effect from the camera centre to the battler, offset by unk_0C and unk_10 on screen, and
 * aims it along the screen line between the two points the scratchpad keeps. */
MATCH void func_801EF0D8(void) {
    u8           timer;
    PartyMember* work;
    s32          angle;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        Battle_CenterCamera();
        Battle_ProjectRange();
        g_ScratchPad.cells.halves[6] = g_Task->unk_2E.half;
        g_ScratchPad.cells.halves[7] = g_Task->unk_30.half;
        func_800B0118();
        WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
        Battle_ProjectRange();
        g_Task->unk_2E.half += g_Task->unk_0C;
        g_Task->unk_30.half += g_Task->unk_10;
        g_ScratchPad.cells.halves[4] = g_Task->unk_2E.half;
        g_ScratchPad.cells.halves[5] = g_Task->unk_30.half;
        angle                        = ratan2(g_ScratchPad.cells.halves[6] - g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[7] - g_ScratchPad.cells.halves[5]);
        work                         = g_Task;
        work->param.unk_0B           = 17;
        work->unk_14                 = angle;
        g_Task->unk_09               = 0;
        g_Task->timer                = 1;
        g_Task->unk_04               = 16;
        g_Task->header.step += 1;
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
}

MATCH void func_801EF270(void) {
    u8 counter;
    g_Task->timer += 3;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 8) {
        g_BattleEffectBattler->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpTimerCallSelector.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt120.h"

#include "overlays/bmagic/Effect_CountUpAndFinishAt136.h"

MATCH void BMagic_DrawWhelpBreath(void) {
    POLY_GT4* prim;
    s32       tpage;
    s32       i;
    s32       inner;
    s32       outer;
    s32       swing;
    s32       prev;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.halves[4] = g_Task->unk_2E.half;
    g_ScratchPad.cells.halves[5] = g_Task->unk_30.half;
    g_ScratchPad.cells.halves[1] = g_Task->unk_14;
    for (i = 1; i < g_Task->timer + 1; i++) {
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + FIXED_MUL(rsin(((i + g_Task->unk_09) << 6) & 0xFC0), 352)) & ANGLE_MASK;
        g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 16);
        g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), 16);
        prim  = (POLY_GT4*)g_GfxPrimCursor;
        inner = ((i - 1 - g_Task->unk_09) & 0x3F) << 6;
        outer = ((i - g_Task->unk_09) & 0x3F) << 6;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] + 0x400) & ANGLE_MASK;
        prev                         = i - 1;
        swing                        = rsin(inner) * 2;
        swing                        = FIXED_MUL(swing, prev) + 4;
        g_ScratchPad.cells.halves[0] = prev * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / g_Task->param.unk_0B + 1;
        prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        swing                        = rsin(outer) * 2;
        swing                        = FIXED_MUL(swing, i) + 4;
        g_ScratchPad.cells.halves[0] = i * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / g_Task->param.unk_0B + 1;
        prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setXY0(prim, g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        prim->x2    = g_ScratchPad.cells.halves[4];
        prim->y2    = g_ScratchPad.cells.halves[5];
        prim->clut  = GetClut(0, 0x1FA);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100);
        setUV4(prim, 0x40, i * 8 - g_Task->unk_09 * 16, 0x80, i * 8 - g_Task->unk_09 * 16, 0x40, i * 8 - g_Task->unk_09 * 16 + 8, 0x80, i * 8 - g_Task->unk_09 * 16 + 8);
        g_ScratchPad.cells.halves[3] = g_Task->unk_04 * 12;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = g_Task->unk_04;
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[1] - 0x400) & ANGLE_MASK;
        swing                        = rsin(inner) * 2;
        swing                        = FIXED_MUL(swing, prev) + 4;
        g_ScratchPad.cells.halves[0] = prev * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / g_Task->param.unk_0B + 1;
        setXY0(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        swing                        = rsin(outer) * 2;
        swing                        = FIXED_MUL(swing, i) + 4;
        g_ScratchPad.cells.halves[0] = i * 4 + swing;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] / g_Task->param.unk_0B + 1;
        prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x1                     = g_ScratchPad.cells.halves[6];
        prim->y1                     = g_ScratchPad.cells.halves[7];
        prim->x3                     = g_ScratchPad.cells.halves[4];
        prim->y3                     = g_ScratchPad.cells.halves[5];
        prim->clut                   = GetClut(0, 0x1FA);
        prim->tpage                  = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100);
        setUV4(prim, 0, i * 8 - g_Task->unk_09 * 16, 0x40, i * 8 - g_Task->unk_09 * 16, 0, i * 8 - g_Task->unk_09 * 16 + 8, 0x40, i * 8 - g_Task->unk_09 * 16 + 8);
        g_ScratchPad.cells.halves[3] = g_Task->unk_04 * 12;
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        g_ScratchPad.cells.halves[3] = g_Task->unk_04;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_GT4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EFDD4(void) {
    PartyMember* work;
    u32          i;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->unk_25    = 29;
    g_Task->unk_26    = 0;
    g_Task->unk_27    = 0xA1;
    g_Task->unk_28    = 0;
    g_Task->unk_2A    = g_BattleEffectBattler->facing & 1;
    g_Task->unk_29    = 3;
    g_Task->unk_24    = 4;
    work              = g_Task;
    work->unk_2B      = 0;
    work->unk_2C.half = 0;
    switch (g_Task->param.unk_0B) {
        case 0:
            g_Task->header.step += 1;
            if (g_Task->facing & 2) {
                g_Task->unk_29 = 4;
                g_Task->unk_2A = ~g_Task->facing & 1;
                Actor_SelectScript(3);
            } else {
                Actor_SelectScript(0);
            }
            break;
        case 1:
            g_Task->unk_09      = 120;
            g_Task->header.step = 2;
            Actor_SelectScript(1);
            break;
        case 2:
            for (i = 0; i < 6; i++) {
                D_801F0D0C[i] = 0;
            }
            g_Task->unk_09      = 0;
            g_Task->header.step = 3;
            break;
        case 3:
            g_Task->unk_09      = 0;
            g_Task->timer       = 80;
            g_Task->header.step = 5;
            break;
    }
}

MATCH void func_801F0008(void) {
    Area_AddGridActor();
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        Effect_Reset();
    }
}

MATCH void func_801F0044(void) {
    u8 count;

    Actor_StepAnimLoop();
    Area_AddGridActor();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Effect_Reset();
    }
}

MATCH void func_801F009C(void) {
    u8 timer;

    func_801F0274();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 96) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0104(void) {
    u8 count;

    func_801F0274();
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x70) {
        Effect_Reset();
    }
}

MATCH void func_801F0158(void) {
    u8 timer;

    func_801F08AC();
    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F01C0(void) {
    u8 count;

    func_801F08AC();
    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F0224(void) {
    u8 count;

    func_801F08AC();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Effect_Reset();
    }
}

MATCH void func_801F0274(void) {
    PartyMember* work;
    s32          tpage;
    u32          j;
    u32          i;
    u8           enemy;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 8; i++) {
            enemy = i;
            if (Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) != 0) {
                continue;
            }
            g_Task->param.unk_0B = j;
            g_Task->timer        = enemy;
            work                 = g_Task;
            work->unk_0C         = D_801F0CE4[j].x;
            work->unk_10         = D_801F0CE4[j].y;
            Effect_RotatePosition(work);
            g_Task->pos.x.fixed = g_BattleEnemyBattlers[i].pos.x.fixed + g_Task->unk_0C;
            g_Task->pos.y.fixed = g_BattleEnemyBattlers[i].pos.y.fixed + g_Task->unk_10;
            g_Task->pos.z.fixed = g_BattleEnemyBattlers[i].pos.z.fixed + D_801F0CE4[j].z;
            g_Task->facing      = g_BattleEnemyBattlers[i].unk_08;
            func_801F078C();
            func_801F04B0();
            PopMatrix();
        }
    }
    for (j = 0; j < 6; j++) {
        if (j * 3 < g_Task->unk_09) {
            D_801F0D0C[j]++;
        }
        if (g_Task->header.step == 3) {
            D_801F0D0C[j] &= 0xF;
        }
    }
}

/* Draw a textured quad for each of the six breath puffs that has started and has not run out:
 * the quad widens and rises and its shade fades as the puff counter grows. */
MATCH void func_801F04B0(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       z;

    for (i = 0; i < 6; i++) {
        if (i * 3 < g_Task->unk_09 && D_801F0D0C[i] < 16) {
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetSemiTrans(prim, 1);
            g_ScratchPad.cells.halves[0] = D_801F0D0C[i] * 4 + 50;
            z                            = D_801F0D0C[i] * 15;
            g_ScratchPadVectors[0].vx    = FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]);
            g_ScratchPadVectors[0].vy    = FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]);
            g_ScratchPadVectors[0].vz    = z;
            setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]), z);
            setVector(&g_ScratchPadVectors[2], FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]), z);
            setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]), z);
            prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
            prim->clut  = GetClut(32, 506);
            setUVWH(prim, 8, 64, 32, 32);
            g_ScratchPad.cells.halves[3] = 97 - D_801F0D0C[i] * 6;
            setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_FT4));
        }
    }
}

MATCH void func_801F078C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    switch (g_Task->facing) {
        case 0:
            rot.vy = 3072;
            break;
        case 1:
            rot.vx = 1024;
            break;
        case 2:
            rot.vy = 1024;
            break;
        case 3:
            rot.vx = 3072;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

MATCH void func_801F08AC(void) {
    PartyMember* work;
    u32          i;

    for (i = 0; i < 8; i++) {
        if (Battle_SlotIsBlocked((i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK) != 0) {
            continue;
        }
        work                     = g_Task;
        work->facing             = g_BattleEnemyBattlers[i].unk_08;
        g_Task->pos.x.fixed      = g_BattleEnemyBattlers[i].pos.x.fixed;
        g_Task->pos.y.fixed      = g_BattleEnemyBattlers[i].pos.y.fixed;
        COORD_INT(g_Task->pos.z) = FIELD(u16, D_801EB66E, i * BATTLE_ENEMY_STRIDE);
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F0974);
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F0974(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      angle;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = (g_FrameCount & 0x3F) + 0x100;
    tpage                        = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    prim                      = GFX_BeginPolyG3(1);
    g_ScratchPadVectors[0].vx = 0;
    g_ScratchPadVectors[0].vy = 0;
    g_ScratchPadVectors[0].vz = 0;
    angle                     = BMAGIC_PHASE_ANGLE((D_801F0D08[g_Task->facing] - 6) & BMAGIC_PHASE_MASK);
    g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(angle), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(angle), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vz = 0;
    angle                     = BMAGIC_PHASE_ANGLE((D_801F0D08[g_Task->facing] + 6) & BMAGIC_PHASE_MASK);
    g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(angle), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(angle), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vz = 0;
    setRGB0(prim, g_Task->unk_09 * 10 + 1, g_Task->unk_09 * 10 + 1, g_Task->unk_09 * 10 + 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, 1, 1, 1);
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
}
#else
INCLUDE_ASM(func_801F0974);
#endif

#include "overlays/bmagic/Effect_SetActorMatrix.h"

#include "magic101_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Magic101Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.mode);
    if (TASK(PartyMember)->timer != 0 && TASK(PartyMember)->header.flags != 0) {
        BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801EF07C);
    }
}

MATCH void func_801EECCC(void) {
    u32 slot;
    u32 counter;

    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing ^ 0x2;
        } else {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing;
        }
    } else {
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing;
        } else {
            TASK(PartyMember)->facing = g_BattleActiveActor->facing ^ 0x2;
        }
    }
    Battle_CenterCamera();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0x30;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.mode += 1;
    counter = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x1B) & BYTE_MASK;
        g_BattleEffects[slot].target.party = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_04       = counter;
        g_BattleEffects[slot].arg.unk_09   = (((counter >> 2) * 3) << 2) + 1;
        TASK(PartyMember)->param.unk_0B += 1;
        counter += 1;
    } while (counter < 0x10);
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEE68(void) {
    u8 timer;

    timer                    = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = timer;
    if (timer == 16) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownTimerNextStep.h"

MATCH void func_801EEF20(void) {
    u8 timer;

    timer                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer;
    if (timer == 0) {
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801EF07C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = FIXED_MUL(rsin((g_FrameCount & 0x1F) << 7), 0x10) + 0x80;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->timer * 6;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);

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
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

/* func_801EF310 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF354(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(D_801EFCE8, func_801EF78C, func_801EF88C);
}

MATCH void func_801EF3DC(void) {
    PartyMember* work;
    u8           counter;
    s32          value;

    counter                   = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = counter;
    if (counter == 0) {
        TASK(PartyMember)->facing       = g_BattleEffectBattler->facing;
        TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed + 0x01800000;
        TASK(PartyMember)->param.unk_0B = TASK(PartyMember)->unk_04 * 0x4 & 0x3F;
        work                            = TASK(PartyMember);
        value                           = D_801EFCC0[work->unk_04];
        work->unk_10                    = 0x60;
        work->unk_14                    = 0x20;
        work->unk_09                    = work->unk_04 * 4 + 1;
        work->unk_0C                    = value << 8;
        TASK(PartyMember)->timer        = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF4DC(void) {
    PartyMember* effect;
    s32          wave;
    u8           timer;

    TASK(PartyMember)->param.unk_0B += 8;
    wave                       = ((rsin((g_FrameCount & 0x1F) << 7) << 5) >> 12) + 384;
    effect                     = TASK(PartyMember);
    effect->pos.z.part.integer = (u16)g_BattleEffectBattler->pos.z.part.integer + wave;
    timer                      = effect->timer + 2;
    effect->timer              = timer;
    if (timer == 16) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF580(void) {
    PartyMember* effect;
    PartyMember* effectForFacing;
    PartyMember* effectForSetup;
    s32          wave;
    u8           ticksRemaining;

    TASK(PartyMember)->param.unk_0B += 8;
    wave                       = ((rsin((g_FrameCount & 0x1F) << 7) << 5) >> 12) + 384;
    effect                     = TASK(PartyMember);
    effect->pos.z.part.integer = (u16)g_BattleEffectBattler->pos.z.part.integer + wave;
    ticksRemaining             = effect->unk_09 - 1;
    effect->unk_09             = ticksRemaining;
    if (ticksRemaining != 0) {
        return;
    }
    if (TASK(PartyMember)->unk_04 == 0) {
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    effectForFacing               = TASK(PartyMember);
    effectForFacing->param.unk_0B = D_801EFCE0[effectForFacing->facing];
    effectForSetup                = TASK(PartyMember);
    effectForSetup->unk_10        = 128;
    effectForSetup->unk_14        = 128;
    effectForSetup->unk_09        = 16;
    effectForSetup->unk_1C        = 24;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF690(void) {
    u8           counter;
    PartyMember* work;

    TASK(PartyMember)->param.unk_0B += 4;
    work = TASK(PartyMember);
    work->unk_10 += work->unk_1C;
    counter      = work->unk_09 - 1;
    work->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF700(void) {
    u8           counter;
    s32          value;
    PartyMember* work;

    TASK(PartyMember)->param.unk_0B += TASK(PartyMember)->timer >> 1;
    work         = TASK(PartyMember);
    counter      = work->timer - 1;
    value        = work->unk_1C - 2;
    work->timer  = counter;
    work->unk_1C = value;
    work->unk_10 += value;
    if (!(counter & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF78C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    if (BATTLE_ACTIVE_WORK->facing & 0x1) {
        setVector(&rot, 0, TASK(PartyMember)->unk_0C, 0);
    } else {
        setVector(&rot, TASK(PartyMember)->unk_0C, 0, 0);
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
}

MATCH void func_801EF88C(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_10 + FIXED_MUL(rsin(0), TASK(PartyMember)->unk_14);
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_10;
    g_ScratchPad.cells.halves[2] = TASK(PartyMember)->param.unk_0B;
    g_ScratchPad.cells.halves[3] = (g_ScratchPad.cells.halves[2] & 0x3F) << 6;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]);
    for (i = 1; i < 32; i++) {
        g_ScratchPad.cells.halves[3] = ((i + g_ScratchPad.cells.halves[2]) & 0x3F) * 64;
        g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_10 + FIXED_MUL(rsin(i << 6), TASK(PartyMember)->unk_14);
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz    = 0;
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[1].vz    = 0;
        g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[3].vx;
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[3].vy;
        g_ScratchPadVectors[2].vz    = 0;
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[3]), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vz    = 0;
        prim                         = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        if (i < 8) {
            g_ScratchPad.cells.halves[4] = TASK(PartyMember)->timer * i;
            g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer;
        } else {
            g_ScratchPad.cells.halves[4] = TASK(PartyMember)->timer << 3;
            g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer;
        }
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4]);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

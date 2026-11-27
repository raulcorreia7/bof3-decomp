#include "magic046_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED28, Effect_MarkDamagedOnZeroTick);

    BMAGIC_RUN_EFFECT_SLOTS(D_801EFF3C, func_801EF324);
}

MATCH void func_801EED28(void) {
    PartyMember* task;
    PartyMember* battler;
    u8           i;
    u8           slot;

    BMAGIC_CLEAR_EFFECTS(i);
    SELF(PartyMember)->facing          = g_BattleEffectBattler->facing;
    battler                            = g_BattleEffectBattler;
    task                               = SELF(PartyMember);
    task->pos.x.fixed                  = battler->pos.x.fixed;
    task->pos.y.fixed                  = battler->pos.y.fixed;
    task->pos.z.fixed                  = battler->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 50);
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    if (g_Battle.encounter != 0 && g_BattleCurrentEnemy->unk_F0 == 0x29) {
        slot                               = Battle_AllocEffect(1, 50);
        g_BattleEffects[slot].target.party = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
    }
    g_GfxPalettePending = 1;
    for (i = 0; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    SELF(PartyMember)->param.unk_0B = 1;
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEF70 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFB4(void) {
    /* Retail dispatches a stack copy of the handlers. */
    MagicModuleSteps handlers;

    handlers = D_801EEC00.steps;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
}

MATCH void func_801EF014(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    work                      = SELF(PartyMember);
    actor                     = g_BattleEffectBattler;
    work->pos.x.fixed         = actor->pos.x.fixed;
    work->pos.y.fixed         = actor->pos.y.fixed;
    z                         = actor->pos.z.fixed;
    work->param.unk_0B        = 0;
    work->pos.z.fixed         = z;
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF090(void) {
    u8 slot;
    u8 tick;

    if (g_FrameCount & 0x1) {
        slot                                   = BMagic_AllocEffect();
        BMAGIC_EFFECT_SLOTS[slot].target.party = SELF(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = SELF(PartyMember)->unk_09;
        tick                                   = SELF(PartyMember)->unk_09;
        if (tick < 100) {
            BMAGIC_EFFECT_SLOTS[slot].unk_0A = 8;
        } else {
            BMAGIC_EFFECT_SLOTS[slot].unk_0A = 8 - (tick - 100) / 4;
        }
        SELF(PartyMember)->param.unk_0B += 1;
    }
    tick                      = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = tick;
    if (tick >= 129U) {
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"

#include "overlays/bmagic/shared/Effect_DispatchStep.h"

MATCH void func_801EF250(void) {
    g_Self                           = g_BattleEffectBattler;
    BATTLE_ACTIVE_WORK->param.unk_0B = 0;
    SELF(PartyMember)->unk_09        = 0;
    Script_Select(2U);
    SELF(PartyMember)->header.mode = 1;
    SELF(PartyMember)->header.step = 1;
}

#include "overlays/bmagic/shared/Effect_AddActor.h"

MATCH void func_801EF304(void) {
    Effect_Reset();
}

MATCH void func_801EF324(void) {
    /* Retail dispatches a stack copy of the handlers. */
    Magic046Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        func_801EFB90();
        func_801EFC48();
        PopMatrix();
    }
}

MATCH void func_801EF3B8(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          angle;

    Battle_CenterCamera();
    angle                     = ratan2(SELF(PartyMember)->pos.x.fixed - g_BattleEffectBattler->pos.x.fixed, SELF(PartyMember)->pos.y.fixed - g_BattleEffectBattler->pos.y.fixed);
    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    switch (g_BattleEnemyBattlers[g_Battle.active_battler - 3].enemy_id.byte.type) {
        /* FAKE: retail compare tree needs a third case above 0x72 on the default body; the bytes keep no value for it. */
        case 0x73:
        default:
            SELF(PartyMember)->unk_0C = 0x6000;
            SELF(PartyMember)->unk_10 = 0;
            SELF(PartyMember)->unk_14 = TO_COORD(64);
            break;
        case 0x10:
            SELF(PartyMember)->unk_0C = 0x10000;
            SELF(PartyMember)->unk_10 = 0;
            SELF(PartyMember)->unk_14 = TO_COORD(128);
            break;
        case 0x72:
            SELF(PartyMember)->unk_0C = 0x1C000;
            SELF(PartyMember)->unk_10 = 0;
            SELF(PartyMember)->unk_14 = TO_COORD(256);
            break;
    }
    Effect_RotatePosition(g_Self);
    work              = SELF(PartyMember);
    actor             = g_BattleEffectBattler;
    work->pos.x.fixed = actor->pos.x.fixed + work->unk_0C;
    work->pos.y.fixed = actor->pos.y.fixed + work->unk_10;
    work->pos.z.fixed = actor->pos.z.fixed + work->unk_14;
    work->unk_09      = 0;
    work->unk_14      = angle & ANGLE_MASK;
    SELF(PartyMember)->header.step++;
}

MATCH void func_801EF540(void) {
    s32 angle;
    s32 phase;
    u8  count;

    phase                     = (SELF(PartyMember)->unk_09 + SELF(PartyMember)->param.unk_0B) & 0x3F;
    SP_REF(s16, 2)            = BMAGIC_PHASE_ANGLE(phase);
    angle                     = SELF(PartyMember)->unk_14 + ((rsin((s16)BMAGIC_PHASE_ANGLE(phase)) * 0x12C) >> 0xC);
    SELF(PartyMember)->unk_0C = angle;
    SELF(PartyMember)->pos.x.fixed += (rsin(angle) * 0x7000) >> 0xC;
    SELF(PartyMember)->pos.y.fixed += (rcos(SELF(PartyMember)->unk_0C) * 0x7000) >> 0xC;
    Battle_ProjectRange();
    func_801EF7E8();
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF660(void) {
    s32 angle;
    s32 phase;
    u8  timer_next;

    phase                     = (SELF(PartyMember)->unk_09 + SELF(PartyMember)->param.unk_0B) & 0x3F;
    SP_REF(s16, 2)            = BMAGIC_PHASE_ANGLE(phase);
    angle                     = SELF(PartyMember)->unk_14 + ((rsin((s16)BMAGIC_PHASE_ANGLE(phase)) * 0x12C) >> 0xC);
    SELF(PartyMember)->unk_0C = angle;
    SELF(PartyMember)->pos.x.fixed += (rsin(angle) * 0x7000) >> 0xC;
    SELF(PartyMember)->pos.y.fixed += (rcos(SELF(PartyMember)->unk_0C) * 0x7000) >> 0xC;
    Battle_ProjectRange();
    func_801EF7E8();
    SELF(PartyMember)->unk_09 += 1;
    timer_next               = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.flags = 0;
        SELF(PartyMember)->header.mode  = 0;
        SELF(PartyMember)->header.step  = 0;
        SELF(PartyMember)->unk_03       = 0;
        SELF(PartyMember)->unk_04       = 0;
    }
}

/* Draw the magic046 glow quad around the effect: the radius grows with byte 0x09, the shade with
 * the timer (byte 0x0A). */
MATCH void func_801EF7E8(void) {
    POLY_GT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    if (SELF(PartyMember)->unk_09 < 8) {
        g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->unk_09 + 1) * 6;
    } else {
        g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 2 + 0x20;
    }
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer * 20;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->screen_y.value;
    setXY4(prim, g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0xC00), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0xC00), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0x800), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0x800), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0x400), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0x400), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 1, 1, 30, 30);
    GFX_SET_RGB_ALL(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[4]);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
}

MATCH void func_801EFB90(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(BATTLE_ACTIVE_WORK);
}

MATCH void func_801EFC48(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->unk_09 + 6) * 10;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer * 6;
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

/* func_801EFED0 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

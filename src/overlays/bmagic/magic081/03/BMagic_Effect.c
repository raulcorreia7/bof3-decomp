#include "magic081_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void BMagic_UpdateRottenBreath(void) {
    Magic010Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, func_801EF330);
}

MATCH void func_801EED44(void) {
    PartyMember*  actor;
    PartyMember*  work;
    BattleEffect* effect;
    PartyMember*  saved;
    u8            index;
    u16           pose;

    for (index = 0; index < BMAGIC_EFFECT_COUNT; index++) {
        BMAGIC_EFFECT_SLOTS[index].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[index].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[index].header.step  = 0;
    }

    actor                    = g_BattleEffectBattler;
    work                     = TASK(PartyMember);
    work->pos.x.fixed        = actor->pos.x.fixed;
    work->pos.y.fixed        = actor->pos.y.fixed;
    pose                     = actor->pos.z.part.integer;
    g_GfxPalettePending      = 1;
    work->pos.z.part.integer = pose;

    for (index = 0; index < 16; index++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[index] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[index] | PSX_COLOR_STP_BIT;
    }

    effect                                                       = D_801EC2E0;
    saved                                                        = TASK(PartyMember);
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_Task                                                       = BattleEffect_GetTarget(effect);
    Script_Select(1);
    g_Task = saved;
    saved->header.mode++;
}

MATCH void func_801EEE74(void) {
    PartyMember* saved;

    saved  = TASK(PartyMember);
    g_Task = D_801EC2E0->target.party;
    if (Script_AnimStepOnce() & BYTE_MASK) {
        saved->header.mode++;
    }
    g_Task = saved;
}

MATCH void func_801EEEDC(void) {
    PartyMember* published;
    PartyMember* saved;
    u8           index;

    index                               = Battle_AllocEffect(1, 66);
    published                           = TASK(PartyMember);
    g_BattleEffects[index].header.mode  = 0;
    saved                               = TASK(PartyMember);
    g_BattleEffects[index].target.party = published;
    g_Task                              = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    g_Task              = saved;
    saved->param.unk_0B = 1;
    TASK(PartyMember)->header.mode++;
}

MATCH void func_801EEF88(void) {
    PartyMember* saved_work;

    saved_work = TASK(PartyMember);
    g_Task     = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    g_Task = saved_work;
    if (saved_work->param.unk_0B == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF014 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF058(void) {
    Magic081Steps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF0B8(void) {
    u32          slot;
    u8           effect_index;
    PartyMember* task;

    TASK(PartyMember)->pos.x.fixed             = g_BattleEffectBattler->pos.x.fixed + TO_COORD(2);
    TASK(PartyMember)->pos.y.fixed             = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(TASK(PartyMember)->pos.z)        = COORD_INT(g_BattleEffectBattler->pos.z);
    slot                                       = Battle_AllocEffect(1, 66);
    effect_index                               = slot & BYTE_MASK;
    task                                       = TASK(PartyMember);
    g_BattleEffects[effect_index].header.mode  = 1;
    g_BattleEffects[effect_index].target.party = task;
    TASK(PartyMember)->timer                   = slot;
    SND_SEQueueSelection(0x100);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF18C(void) {
    u8 slot;
    u8 tick;

    if ((g_FrameCount & 0x3) == 0x3) {
        slot                                   = BMagic_AllocEffect();
        BMAGIC_EFFECT_SLOTS[slot].target.party = TASK(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = TASK(PartyMember)->unk_09;
        tick                                   = TASK(PartyMember)->unk_09;
        if (tick < 100) {
            BMAGIC_EFFECT_SLOTS[slot].unk_0A = 8;
        } else {
            BMAGIC_EFFECT_SLOTS[slot].unk_0A = 8 - (tick - 100) / 4;
        }
        TASK(PartyMember)->param.unk_0B += 1;
    }
    tick                      = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = tick;
    if (tick >= 129U) {
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    if (g_Battle.flags & BATTLE_STATE_EFFECT_PLAYING) {
        Effect_Reset();
    } else {
        Battle_CenterCamera();
    }
}

MATCH void func_801EF330(void) {
    Magic081SecondSteps handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF39C(void) {
    u8 effect_slot;

    TASK(PartyMember)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + TO_COORD(1) / 8;
    TASK(PartyMember)->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(TASK(PartyMember)->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 256;
    effect_slot                         = g_BattleEffectBattler->timer;
    TASK(PartyMember)->unk_14           = ratan2(g_BattleEffects[effect_slot].pos.x.fixed - TASK(PartyMember)->pos.x.fixed, g_BattleEffects[effect_slot].pos.y.fixed - TASK(PartyMember)->pos.y.fixed);
    TASK(PartyMember)->unk_09           = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF44C(void) {
    s32 angle;
    s32 phase;
    u8  count;

    phase                     = (TASK(PartyMember)->unk_09 + TASK(PartyMember)->param.unk_0B) & 0x3F;
    SP_REF(s16, 2)            = BMAGIC_PHASE_ANGLE(phase);
    angle                     = TASK(PartyMember)->unk_14 + ((rsin((s16)BMAGIC_PHASE_ANGLE(phase)) * 0x12C) >> 0xC);
    TASK(PartyMember)->unk_0C = angle;
    TASK(PartyMember)->pos.x.fixed += (rsin(angle) * 0x7000) >> 0xC;
    TASK(PartyMember)->pos.y.fixed += (rcos(TASK(PartyMember)->unk_0C) * 0x7000) >> 0xC;
    Battle_ProjectRange();
    func_801EF6A0();
    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        TASK(PartyMember)->timer = 64;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF57C(void) {
    u8 timer;
    func_800AF2B4((BattleRange*)&g_BattleEffects[g_BattleEffectBattler->timer], 3);
    Battle_ProjectRange();
    func_801EF6A0();
    timer                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer;
    if (timer == 0) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF614(void) {
    Battle_ProjectRange();
    func_801EF6A0();
    BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
    TASK(PartyMember)->header.flags = 0;
    TASK(PartyMember)->header.mode  = 0;
    TASK(PartyMember)->header.step  = 0;
    TASK(PartyMember)->unk_03       = 0;
    TASK(PartyMember)->unk_04       = 0;
}

/* Draws the effect glow as one textured quad around its screen point; the radius grows with the timer up to 0x40. */
MATCH void func_801EF6A0(void) {
    POLY_GT4* prim;
    s16*      shade;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    if (TASK(PartyMember)->unk_09 < 8) {
        g_ScratchPad.cells.halves[0] = (TASK(PartyMember)->unk_09 + 1) * 8;
    } else {
        g_ScratchPad.cells.halves[0] = 0x40;
    }
    shade                        = &g_ScratchPad.cells.halves[4];
    *shade                       = 0x80;
    g_ScratchPad.cells.halves[2] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[3] = TASK(PartyMember)->screen_y.value;
    setXY4(prim, g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0xC00), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0xC00), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0x800), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0x800), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0x400), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0x400), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 1, 1, 30, 30);
    GFX_SET_RGB_ALL(prim, *shade, *shade, *shade);
    SetSemiTrans(prim, 1);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
}

/* func_801EFA20 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

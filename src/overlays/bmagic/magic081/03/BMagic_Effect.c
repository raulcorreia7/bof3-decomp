#include "magic081_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void BMagic_UpdateRottenBreath(void) {
    Magic010Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.mode);

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
    work                     = SELF(PartyMember);
    work->pos.x.fixed        = actor->pos.x.fixed;
    work->pos.y.fixed        = actor->pos.y.fixed;
    pose                     = actor->pos.z.part.integer;
    g_GfxPalettePending      = 1;
    work->pos.z.part.integer = pose;

    for (index = 0; index < 16; index++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[index] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[index] | PSX_COLOR_STP_BIT;
    }

    effect                                                       = D_801EC2E0;
    saved                                                        = SELF(PartyMember);
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_Self                                                       = BattleEffect_GetTarget(effect);
    Script_Select(1);
    g_Self = saved;
    saved->header.mode++;
}

MATCH void func_801EEE74(void) {
    PartyMember* saved;

    saved  = SELF(PartyMember);
    g_Self = D_801EC2E0->target.party;
    if (Script_AnimStepOnce() & BYTE_MASK) {
        saved->header.mode++;
    }
    g_Self = saved;
}

MATCH void func_801EEEDC(void) {
    PartyMember* published;
    PartyMember* saved;
    u8           index;

    index                               = Battle_AllocEffect(1, 66);
    published                           = SELF(PartyMember);
    g_BattleEffects[index].header.mode  = 0;
    saved                               = SELF(PartyMember);
    g_BattleEffects[index].target.party = published;
    g_Self                              = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    g_Self              = saved;
    saved->param.unk_0B = 1;
    SELF(PartyMember)->header.mode++;
}

MATCH void func_801EEF88(void) {
    PartyMember* saved_work;

    saved_work = SELF(PartyMember);
    g_Self     = D_801EC2E0->target.party;
    Script_AnimStepOnce();
    g_Self = saved_work;
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
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
}

MATCH void func_801EF0B8(void) {
    u32          slot;
    u8           effect_index;
    PartyMember* task;

    SELF(PartyMember)->pos.x.fixed             = g_BattleEffectBattler->pos.x.fixed + TO_COORD(2);
    SELF(PartyMember)->pos.y.fixed             = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(SELF(PartyMember)->pos.z)        = COORD_INT(g_BattleEffectBattler->pos.z);
    slot                                       = Battle_AllocEffect(1, 66);
    effect_index                               = slot & BYTE_MASK;
    task                                       = SELF(PartyMember);
    g_BattleEffects[effect_index].header.mode  = 1;
    g_BattleEffects[effect_index].target.party = task;
    SELF(PartyMember)->timer                   = slot;
    SND_SEQueueSelection(0x100);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF18C(void) {
    u8 slot;
    u8 tick;

    if ((g_FrameCount & 0x3) == 0x3) {
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
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
}

MATCH void func_801EF39C(void) {
    u8 effect_slot;

    SELF(PartyMember)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + TO_COORD(1) / 8;
    SELF(PartyMember)->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 256;
    effect_slot                         = g_BattleEffectBattler->timer;
    SELF(PartyMember)->unk_14           = ratan2(g_BattleEffects[effect_slot].pos.x.fixed - SELF(PartyMember)->pos.x.fixed, g_BattleEffects[effect_slot].pos.y.fixed - SELF(PartyMember)->pos.y.fixed);
    SELF(PartyMember)->unk_09           = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF44C(void) {
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
    func_801EF6A0();
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        SELF(PartyMember)->timer = 64;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF57C(void) {
    u8 timer;
    func_800AF2B4((BattleRange*)&g_BattleEffects[g_BattleEffectBattler->timer], 3);
    Battle_ProjectRange();
    func_801EF6A0();
    timer                    = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF614(void) {
    Battle_ProjectRange();
    func_801EF6A0();
    BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
    SELF(PartyMember)->header.flags = 0;
    SELF(PartyMember)->header.mode  = 0;
    SELF(PartyMember)->header.step  = 0;
    SELF(PartyMember)->unk_03       = 0;
    SELF(PartyMember)->unk_04       = 0;
}

/* Draws the effect glow as one textured quad around its screen point; the radius grows with the timer up to 0x40. */
MATCH void func_801EF6A0(void) {
    POLY_GT4* prim;
    s16*      shade;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    if (SELF(PartyMember)->unk_09 < 8) {
        g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->unk_09 + 1) * 8;
    } else {
        g_ScratchPad.cells.halves[0] = 0x40;
    }
    shade                        = &g_ScratchPad.cells.halves[4];
    *shade                       = 0x80;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->screen_y.value;
    setXY4(prim, g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0xC00), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0xC00), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0x800), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0x800), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[2] + FIXED_MUL(rsin(0x400), g_ScratchPad.cells.halves[0]), g_ScratchPad.cells.halves[3] + FIXED_MUL(rcos(0x400), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 1, 1, 30, 30);
    GFX_SET_RGB_ALL(prim, *shade, *shade, *shade);
    SetSemiTrans(prim, 1);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
}

/* func_801EFA20 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

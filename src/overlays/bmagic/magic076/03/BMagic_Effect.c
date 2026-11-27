#include "magic076_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    Magic076MainSteps handlers;
    PartyMember*      saved_task;
    PartyMember*      saved_battler;
    u8                i;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, func_801EF8A8);
}

MATCH void func_801EED48(void) {
    PartyMember* actor;
    PartyMember* owner;
    u16          i;
    u8           slot;

    BMAGIC_CLEAR_EFFECTS(i);
    SELF(PartyMember)->unk_04       = func_801EF2E8();
    actor                           = g_Battle.selected_actor;
    SELF(PartyMember)->facing       = actor->facing;
    SELF(PartyMember)->pos.x.fixed  = actor->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed  = actor->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed  = actor->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 60;
    SELF(PartyMember)->timer        = 0;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 98);
    owner                              = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].target.party = owner;
    SELF(PartyMember)->param.unk_0B += 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    for (i = 0; i < AREA_PALETTE_COLORS; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] | PSX_COLOR_STP_BIT;
    }
    for (i = 0; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BMAGIC_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00)[i] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors[0]   = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors[0];
    g_GfxPalettePending                                          = 1;
}

/* func_801EEF5C */
#include "overlays/bmagic/shared/Effect_PreparePalette.h"

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

/* func_801EF11C */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(1);
}

MATCH void Effect_DarkenPalette(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g--;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b--;
    if (--SELF(PartyMember)->unk_09 == 0) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        SELF(PartyMember)->header.mode++;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* Whether the queued action is an ability other than Raise Dead (the spell or the skill). */
MATCH u8 func_801EF2E8(void) {
    if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_Battle.action_id)) {
            case ABILITY_RAISE_DEAD:
            case ABILITY_RAISE_DEAD_SKILL:
                return 0;
            default:
                return 1;
            case ABILITY_RESURRECT:
                return 1;
        }
    }
    return 0;
}

/* func_801EF330 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF374(void) {
    SYS_DISPATCH_BYTE(D_801F048C, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        func_801EF698();
    }
}

MATCH void func_801EF3F4(void) {
    PartyMember* work;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->unk_04 = g_BattleEffectBattler->unk_04;
        work                      = SELF(PartyMember);
        work->pos.x.fixed         = g_BattleEffectBattler->pos.x.fixed;
        work->pos.y.fixed         = g_BattleEffectBattler->pos.y.fixed;
        work->pos.z.fixed         = g_BattleEffectBattler->pos.z.fixed + 0x00C00000;
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->timer  = 60;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF4A8(void) {
    PartyMember* battler;
    u8           tick;
    u8           i;
    u8           slot;

    tick                      = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = tick;
    if (tick == 16) {
        for (i = 0; i < D_801F049C[SELF(PartyMember)->unk_04]; i++) {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                battler                                = g_BattleEffectBattler;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = RANDOM_MASK(0xF) + 16;
                g_BattleEffectBattler->param.unk_0B += 1;
            }
        }
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801EF698(void) {
    POLY_FT4* prim;
    s16       x;
    s16       y;
    s16       half_w;
    s16       height;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 1, sizeof(DR_MODE));
    if (SELF(PartyMember)->unk_04 != 0) {
        height = 0x60;
        half_w = 0x38;
    } else {
        height = 0x40;
        half_w = 0x18;
    }
    prim                         = (POLY_FT4*)g_GfxPrimCursor;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 << 3;
    x                            = SELF(PartyMember)->screen_x.value;
    y                            = SELF(PartyMember)->screen_y.value;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x - half_w, y - height, x + half_w, y - height, x - half_w, y, x + half_w, y);
    prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 0x340, 0x100);
    prim->clut  = GetClut(0, 0x1FA);
    if (SELF(PartyMember)->unk_04 != 0) {
        setUVWH(prim, 8, 8, 112, 96);
    } else {
        setUVWH(prim, 0x78, 8, 48, 64);
    }
    setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 1, sizeof(POLY_FT4));
}

MATCH void func_801EF8A8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Self);
}

#include "overlays/bmagic/shared/Effect_DrawRings.h"

MATCH void func_801EFA60(void) {
    s16* angle;
    s32  speed;
    u8   count;
    u8   phase;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (SELF(PartyMember)->param.unk_0B == 0) {
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x01));
        }
        SELF(PartyMember)->unk_0C      = 8;
        angle                          = &g_ScratchPad.cells.halves[2];
        phase                          = SELF(PartyMember)->param.unk_0B & 0xF;
        *angle                         = phase << 8;
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(phase << 8) * SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle) * SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        speed                          = ((rand() & 3) << 20) + 0x200000;
        SELF(PartyMember)->unk_14      = speed;
        SELF(PartyMember)->unk_20      = speed / 16;
        SELF(PartyMember)->unk_5D      = (RANDOM_MASK(7)) + 6;
        SELF(PartyMember)->unk_5E      = (RANDOM_MASK(7)) + 6;
        SELF(PartyMember)->unk_5F      = (RANDOM_MASK(7)) + 6;
        SELF(PartyMember)->unk_09      = 0;
        SELF(PartyMember)->timer       = 16;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFC30 */
#include "overlays/bmagic/shared/Effect_SpreadAlongAngleAndStep.h"

/* func_801EFD60 */
#include "overlays/bmagic/shared/Effect_SpreadAlongAngleAndClear.h"

#include "overlays/bmagic/shared/BMagic_DrawRingTriangles.h"

#include "overlays/bmagic/shared/BMagic_DrawRingQuads.h"

/* func_801F03D4 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0438 */
#include "overlays/bmagic/shared/Actor_Clear.h"

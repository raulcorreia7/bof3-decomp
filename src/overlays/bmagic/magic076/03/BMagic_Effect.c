#include "magic076_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC28);

MATCH void func_801EED48(void) {
    PartyMember* actor;
    PartyMember* owner;
    u16          i;
    u8           slot;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    g_Task->unk_04       = func_801EF2E8();
    actor                = g_Battle.selected_actor;
    g_Task->facing       = actor->facing;
    g_Task->pos.x.fixed  = actor->pos.x.fixed;
    g_Task->pos.y.fixed  = actor->pos.y.fixed;
    g_Task->pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 60;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 98);
    owner                              = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].target.party = owner;
    g_Task->param.unk_0B += 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    for (i = 0; i < 256; i++) {
        MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[i] = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW)[i] | 0x8000;
    }
    for (i = 0; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00)[i] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                      = 1;
}

/* func_801EEF5C */
#include "overlays/bmagic/Effect_PreparePalette.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

/* func_801EF11C */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(1);
}

MATCH void Effect_DarkenPalette(void) {
    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        g_Task->header.mode++;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

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
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF374(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EF698();
    }
}

MATCH void func_801EF3F4(void) {
    PartyMember* work;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_04    = g_BattleEffectBattler->unk_04;
        work              = g_Task;
        work->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        work->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x00C00000;
        g_Task->unk_09    = 0;
        g_Task->timer     = 60;
        g_Task->header.step++;
    }
}

MATCH void func_801EF4A8(void) {
    PartyMember* battler;
    u8           tick;
    u8           i;
    u8           slot;

    tick           = g_Task->unk_09 + 1;
    g_Task->unk_09 = tick;
    if (tick == 16) {
        for (i = 0; i < D_801F049C[g_Task->unk_04]; i++) {
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
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801EF698(void) {
    POLY_FT4* prim;
    s16       x;
    s16       y;
    s16       half_w;
    s16       height;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(DR_MODE));
    if (g_Task->unk_04 != 0) {
        height = 0x60;
        half_w = 0x38;
    } else {
        height = 0x40;
        half_w = 0x18;
    }
    prim                             = (POLY_FT4*)g_GfxPrimCursor;
    D_1F800000.view.effect.params[3] = g_Task->unk_09 << 3;
    x                                = g_Task->unk_2E.half;
    y                                = g_Task->unk_30.half;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x - half_w, y - height, x + half_w, y - height, x - half_w, y, x + half_w, y);
    prim->tpage = GetTPage(1, 1, 0x340, 0x100);
    prim->clut  = GetClut(0, 0x1FA);
    if (g_Task->unk_04 != 0) {
        setUVWH(prim, 8, 8, 112, 96);
    } else {
        setUVWH(prim, 0x78, 8, 48, 64);
    }
    setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));
}

MATCH void func_801EF8A8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

#include "overlays/bmagic/Effect_DrawRings.h"

MATCH void func_801EFA60(void) {
    s16* angle;
    s32  speed;
    u8   count;
    u8   phase;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (g_Task->param.unk_0B == 0) {
            SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x01));
        }
        g_Task->unk_0C      = 8;
        angle               = &D_1F800000.view.effect.params[2];
        phase               = g_Task->param.unk_0B & 0xF;
        *angle              = phase << 8;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(phase << 8) * g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle) * g_Task->unk_0C;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        speed               = ((rand() & 3) << 20) + 0x200000;
        g_Task->unk_14      = speed;
        g_Task->unk_20      = speed / 16;
        g_Task->unk_5D      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_5E      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_5F      = (RANDOM_MASK(7)) + 6;
        g_Task->unk_09      = 0;
        g_Task->timer       = 16;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFC30(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 2;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if (count == 16) {
        g_Task->header.step++;
    }
}

MATCH void func_801EFD60(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    if (g_FrameCount & 0x1) {
        count          = g_Task->unk_09 - 1;
        g_Task->unk_09 = count;
        if (count == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            Actor_Clear();
        }
    }
}

INCLUDE_ASM(BMagic_DrawRingTriangles);

INCLUDE_ASM(BMagic_DrawRingQuads);

/* func_801F03D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0438 */
#include "overlays/bmagic/Actor_Clear.h"

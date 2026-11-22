#include "magic169_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC38(void) {
    Magic010Steps handlers;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, BMAGIC_WORK->header.mode);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.mode != 0) {
        func_800AF764();
        func_801EF070();
    }
    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, func_801EF860);
}

MATCH void func_801EED8C(void) {
    u16* src;
    u16* dst;
    u16  i;

    BMAGIC_CLEAR_EFFECTS(i);
    func_800AFD9C();
    BMAGIC_WORK->pos.z.fixed += TO_COORD(192);
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    MEM(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW)) = MEM(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW));
    g_GfxPalettePending                                          = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    BMAGIC_WORK->unk_09       = 0;
    BMAGIC_WORK->param.unk_0B = 0;
    BMAGIC_WORK->header.mode += 1;
}

MATCH void func_801EEEB0(void) {
    u8           i;
    u8           row = 0;
    u32          slot;
    PartyMember* work;

    if (++BMAGIC_WORK->unk_09 == 16) {
        if (g_Battle.target_selector & BATTLE_TARGET_PARTY_SIDE) {
            i = 0;
            if (g_Battle.party_count != 0) {
                do {
                    slot                               = Battle_AllocEffect(1, 8) & BYTE_MASK;
                    work                               = g_Task;
                    g_BattleEffects[slot].header.mode  = 0;
                    g_BattleEffects[slot].unk_04       = i;
                    g_BattleEffects[slot].arg.unk_09   = row * 0x28 + 1;
                    g_BattleEffects[slot].target.party = work;
                    BMAGIC_WORK->param.unk_0B += 1;
                    row++, i++;
                } while (i < g_Battle.party_count);
            }
        }
        BMAGIC_WORK->header.mode += 1;
    }
}

MATCH void func_801EEFE0(void) {
    u8 timer;

    if (BMAGIC_WORK->param.unk_0B == 0) {
        timer               = BMAGIC_WORK->unk_09 - 1;
        BMAGIC_WORK->unk_09 = timer;
        if (!(timer & BYTE_MASK)) {
            BMAGIC_WORK->header.mode += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EF070(void) {
    POLY_FT4* prim;
    s16*      shade;
    s32       tpage;
    s16       x;
    s16       y;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 1, sizeof(DR_MODE));
    shade  = &D_1F800006;
    prim   = (POLY_FT4*)g_GfxPrimCursor;
    *shade = BMAGIC_WORK->unk_09 * 8;
    x      = BMAGIC_WORK->screen_x.value;
    y      = BMAGIC_WORK->screen_y.value;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x - 0x38, y - 0x60, x + 0x38, y - 0x60, x - 0x38, y, x + 0x38, y);
    prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 8, 8, 112, 96);
    setRGB0(prim, *shade, *shade, *shade);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 1, sizeof(POLY_FT4));
}

/* func_801EF210 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF254(void) {
    BMagicEffectSteps handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC14, header.step);
}

MATCH void func_801EF2CC(void) {
    u8           count;
    u8           i;
    u8           slot;
    PartyMember* actor;
    PartyMember* work;

    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (count == 0) {
        actor               = &g_Game.members[BMAGIC_WORK->unk_04];
        BMAGIC_WORK->facing = actor->facing;
        WorldPos_Copy(&BMAGIC_WORK->pos, &actor->pos);
        BMAGIC_WORK->param.unk_0B = 0;
        BMAGIC_WORK->unk_09       = 8;
        BMAGIC_WORK->timer        = 0;
        BMAGIC_WORK->header.step += 1;
        i = 0;
        do {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                   = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = ((i & BYTE_MASK) >> 2) + 0x10;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                BMAGIC_WORK->param.unk_0B += 1;
            }
            i++;
        } while (i < 24);
    }
}

MATCH void func_801EF444(void) {
    PartyMember* battler;
    u8           timer;
    PartyMember* work;

    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    battler      = &g_Game.members[work->unk_04];
    if (!(timer & BYTE_MASK)) {
        GFX_PaletteFreeFadeTarget(battler);
        BMAGIC_WORK->timer  = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
        BMAGIC_WORK->unk_09 = 8;
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF4FC(void) {
    s32 cue;

    g_PaletteFades[BMAGIC_WORK->timer].offset.r++;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g++;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b++;
    if (--BMAGIC_WORK->unk_09 == 0) {
        cue = EMI_SE_ID(SND_BANK_COMMON, 0x02);
        if (BMAGIC_WORK->unk_04 & 0x1) {
            cue = EMI_SE_ID(SND_BANK_COMMON, 0x01);
        }
        SND_SEQueueSelection(cue);
        BMAGIC_WORK->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_NextStepUnderTickLimit.h"

/* Darkens the palette fade row the effect timer indexes and, when its wait runs out, frees the battler byte 0x04
 * names and tells the battle UI. */
MATCH void func_801EF688(void) {
    u8           count;
    u8           unk04;
    PartyMember* battler;

    /* FAKE: retail frame reserves 0x10 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 0x10);

    unk04 = BMAGIC_WORK->unk_04;
    g_PaletteFades[BMAGIC_WORK->timer].offset.r -= 1;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g -= 1;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b -= 1;
    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    battler             = &g_Game.members[unk04];
    if (!(count & BYTE_MASK)) {
        GFX_PaletteFreeFadeTarget(battler);
        Battle_FadePoisonedBattler(BMAGIC_WORK->unk_04);
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF7D0(void) {
    if (BMAGIC_WORK->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        if (Battle_SlotIsBlocked(BMAGIC_WORK->unk_04) & BYTE_MASK) {
            Battle_MarkDamaged(BMAGIC_WORK->unk_04);
        }
        Effect_Reset();
    }
}

MATCH void func_801EF860(void) {
    SYS_DISPATCH_TASK(D_801F0420, 1, g_Task);
}

#include "overlays/bmagic/shared/Effect_DrawRings.h"

MATCH void func_801EFA18(void) {
    s32  phase;
    s32  speed;
    s16* angle_cell;
    u8   count;

    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (count == 0) {
        BMAGIC_WORK->unk_0C      = 8;
        angle_cell               = &D_1F800004;
        phase                    = BMAGIC_WORK->param.unk_0B & 0xF;
        *angle_cell              = phase << 8;
        BMAGIC_WORK->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * BMAGIC_WORK->unk_0C;
        BMAGIC_WORK->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * BMAGIC_WORK->unk_0C;
        BMAGIC_WORK->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        speed                    = ((RANDOM_MASK(3)) << 20) + 0x200000;
        BMAGIC_WORK->unk_14      = speed;
        BMAGIC_WORK->unk_20      = speed / 16;
        BMAGIC_WORK->unk_5D      = (RANDOM_MASK(7)) + 6;
        BMAGIC_WORK->unk_5E      = (RANDOM_MASK(7)) + 6;
        BMAGIC_WORK->unk_5F      = (RANDOM_MASK(7)) + 6;
        BMAGIC_WORK->unk_09      = 0;
        BMAGIC_WORK->timer       = 16;
        BMAGIC_WORK->header.step++;
    }
}

/* func_801EFBC4 */
#include "overlays/bmagic/shared/Effect_SpreadAlongAngleAndStep.h"

/* func_801EFCF4 */
#include "overlays/bmagic/shared/Effect_SpreadAlongAngleAndClear.h"

#include "overlays/bmagic/shared/BMagic_DrawRingTriangles.h"

#include "overlays/bmagic/shared/BMagic_DrawRingQuads.h"

/* func_801F0368 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F03CC */
#include "overlays/bmagic/shared/Actor_Clear.h"

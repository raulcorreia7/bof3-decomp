#include "magic111_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC7C(void) {
    PartyMember* work;
    u32          index;
    PartyMember* owner;

    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&TASK(PartyMember)->pos, &g_BattleEffectBattler->pos);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.mode += 1;
    index = Battle_AllocEffect(1, 87) & BYTE_MASK;
    Effect_CopyActiveBattlerToSlot(index);
    work                                = TASK(PartyMember);
    g_BattleEffects[index].header.mode  = 0;
    g_BattleEffects[index].header.step  = 0;
    g_BattleEffects[index].unk_06       = 1;
    g_BattleEffects[index].effect_type  = 87;
    g_BattleEffects[index].target.party = work;
    TASK(PartyMember)->param.unk_0B++;
    index                               = Battle_AllocEffect(1, 87) & BYTE_MASK;
    work                                = TASK(PartyMember);
    g_BattleEffects[index].header.mode  = 1;
    g_BattleEffects[index].target.party = work;
    TASK(PartyMember)->param.unk_0B++;
    index                               = Battle_AllocEffect(1, 87) & BYTE_MASK;
    owner                               = TASK(PartyMember);
    g_BattleEffects[index].header.mode  = 2;
    g_BattleEffects[index].target.party = owner;
    TASK(PartyMember)->param.unk_0B++;
    SND_SEQueueSelection(0x100);
    SND_SEQueueSelection(0x101);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EEF44(void) {
    if (TASK(PartyMember)->param.unk_0B == 0) {
        Battle_SelectActiveBattlerScript(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_MarkDamaged(g_Battle.target_selector);
        TASK(PartyMember)->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

/* func_801EEFF8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF03C(void) {
    Magic111Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF0C0(void) {
    PartyMember* work;

    work              = TASK(PartyMember);
    work->unk_29      = 2;
    work              = TASK(PartyMember);
    work->header.step = (work->header.step + 1);
}

MATCH void func_801EF0F0(void) {
    u8           step;
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    step = work->param.unk_0B;
    if (step < 2) {
        work->param.unk_0B             = step - 1;
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF138(void) {
    Effect_Reset();
}

MATCH void func_801EF158(void) {
    SYS_DISPATCH_BYTE(D_801EFAA8, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        TASK(PartyMember)->unk_0C++;
        TASK(PartyMember)->unk_10++;
        func_801EF330();
    }
}

MATCH void func_801EF1D4(void) {
    s32 start;

    start                     = RANDOM_MASK(0x3F);
    TASK(PartyMember)->unk_0C = start;
    TASK(PartyMember)->unk_10 = start + 0x1F;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->timer  = 60;
    TASK(PartyMember)->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

/* Draws a full-screen semi-transparent glow quad: each corner takes its colour from the sines of two angles that
 * follow the effect counters 0x0C and 0x10, scaled by the effect tick. */
MATCH void func_801EF330(void) {
    POLY_G4* prim;
    s32      tpage;
    u8       r;
    u8       g;
    u8       b;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0, 319, 239);
    g_ScratchPadHalves[0] = (TASK(PartyMember)->unk_0C & 0x3F) << 6;
    D_1F800002            = (TASK(PartyMember)->unk_10 & 0x3F) << 6;
    r                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(g_ScratchPadHalves[0]), 6) + 8);
    g                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    b                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    setRGB0(prim, r, g, b);
    g_ScratchPadHalves[0] = ((TASK(PartyMember)->unk_0C + 0xF) & 0x3F) << 6;
    D_1F800002            = ((TASK(PartyMember)->unk_10 + 0xF) & 0x3F) << 6;
    r                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    g                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(g_ScratchPadHalves[0]), 6) + 8);
    b                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    setRGB1(prim, r, g, b);
    g_ScratchPadHalves[0] = ((TASK(PartyMember)->unk_0C + 0x1F) & 0x3F) << 6;
    D_1F800002            = ((TASK(PartyMember)->unk_10 + 0x1F) & 0x3F) << 6;
    r                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    g                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    b                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(g_ScratchPadHalves[0]), 6) + 8);
    setRGB2(prim, r, g, b);
    g_ScratchPadHalves[0] = ((TASK(PartyMember)->unk_0C + 0x2F) & 0x3F) << 6;
    D_1F800002            = ((TASK(PartyMember)->unk_10 + 0x2F) & 0x3F) << 6;
    r                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(g_ScratchPadHalves[0]), 6) + 8);
    g                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(g_ScratchPadHalves[0]), 6) + 8);
    b                     = TASK(PartyMember)->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    setRGB3(prim, r, g, b);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

MATCH void func_801EF7F8(void) {
    SYS_DISPATCH_BYTE(D_801EFAB8, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        func_801EF970();
    }
}

MATCH void func_801EF870(void) {
    if (g_BattleEffectBattler->param.unk_0B < 3U) {
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpByTwoAndStep.h"

MATCH void Effect_TickOnTimerZero2(void) {
    PartyMember* work;

    BMAGIC_TICK_ON_TIMER_ZERO(2);
}

#include "overlays/bmagic/shared/Effect_DrawFullScreenQuad.h"

MATCH void func_801EF970(void) {
    POLY_F4* prim;
    s32      shade;
    s32      tpage;

    EFFECT_DRAW_FULL_SCREEN_QUAD(BMAGIC_LAYER_OVER_BATTLERS);
}

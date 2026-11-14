#include "magic111_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

#include "overlays/bmagic/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC7C(void) {
    PartyMember* work;
    u32          index;
    PartyMember* owner;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    index = Battle_AllocEffect(1, 87) & BYTE_MASK;
    Effect_CopyActiveBattlerToSlot(index);
    work                                 = g_Task;
    g_BattleEffects[index].header.mode   = 0;
    g_BattleEffects[index].header.step   = 0;
    g_BattleEffects[index].unk_06        = 1;
    g_BattleEffects[index].handler_index = 87;
    g_BattleEffects[index].target.party  = work;
    g_Task->param.unk_0B++;
    index                               = Battle_AllocEffect(1, 87) & BYTE_MASK;
    work                                = g_Task;
    g_BattleEffects[index].header.mode  = 1;
    g_BattleEffects[index].target.party = work;
    g_Task->param.unk_0B++;
    index                               = Battle_AllocEffect(1, 87) & BYTE_MASK;
    owner                               = g_Task;
    g_BattleEffects[index].header.mode  = 2;
    g_BattleEffects[index].target.party = owner;
    g_Task->param.unk_0B++;
    SND_QueueSelectionEffect(0x100);
    SND_QueueSelectionEffect(0x101);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EEF44(void) {
    if (g_Task->param.unk_0B == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

/* func_801EEFF8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF03C(void) {
    Magic111Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

MATCH void func_801EF0C0(void) {
    PartyMember* work;

    work              = g_Task;
    work->unk_29      = 2;
    work              = g_Task;
    work->header.step = (work->header.step + 1);
}

MATCH void func_801EF0F0(void) {
    u8           step;
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    step = work->param.unk_0B;
    if (step < 2) {
        work->param.unk_0B  = step - 1;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF138(void) {
    func_801E5988();
}

MATCH void func_801EF158(void) {
    SYS_DISPATCH_BYTE(D_801EFAA8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        g_Task->unk_0C++;
        g_Task->unk_10++;
        func_801EF330();
    }
}

MATCH void func_801EF1D4(void) {
    s32 start;

    start          = RANDOM_MASK(0x3F);
    g_Task->unk_0C = start;
    g_Task->unk_10 = start + 0x1F;
    g_Task->unk_09 = 0;
    g_Task->timer  = 60;
    g_Task->header.step += 1;
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

/* Draws a full-screen semi-transparent glow quad: each corner takes its colour from the sines of two angles that
 * follow the effect counters 0x0C and 0x10, scaled by the effect tick. */
MATCH void func_801EF330(void) {
    POLY_G4* prim;
    s32      tpage;
    u8       r;
    u8       g;
    u8       b;

    tpage = getTPage(0, 2, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0, 319, 239);
    D_1F800000_HALF[0] = (g_Task->unk_0C & 0x3F) << 6;
    D_1F800002         = (g_Task->unk_10 & 0x3F) << 6;
    r                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800000_HALF[0]), 6) + 8);
    g                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    b                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    setRGB0(prim, r, g, b);
    D_1F800000_HALF[0] = ((g_Task->unk_0C + 0xF) & 0x3F) << 6;
    D_1F800002         = ((g_Task->unk_10 + 0xF) & 0x3F) << 6;
    r                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    g                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800000_HALF[0]), 6) + 8);
    b                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    setRGB1(prim, r, g, b);
    D_1F800000_HALF[0] = ((g_Task->unk_0C + 0x1F) & 0x3F) << 6;
    D_1F800002         = ((g_Task->unk_10 + 0x1F) & 0x3F) << 6;
    r                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    g                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    b                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800000_HALF[0]), 6) + 8);
    setRGB2(prim, r, g, b);
    D_1F800000_HALF[0] = ((g_Task->unk_0C + 0x2F) & 0x3F) << 6;
    D_1F800002         = ((g_Task->unk_10 + 0x2F) & 0x3F) << 6;
    r                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800000_HALF[0]), 6) + 8);
    g                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800000_HALF[0]), 6) + 8);
    b                  = g_Task->unk_09 * (FIXED_MUL(rsin(D_1F800002), 6) + 8);
    setRGB3(prim, r, g, b);
    GFX_AddPrim(3, sizeof(POLY_G4));
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
}

MATCH void func_801EF7F8(void) {
    SYS_DISPATCH_BYTE(D_801EFAB8, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF970();
    }
}

MATCH void func_801EF870(void) {
    if (g_BattleEffectBattler->param.unk_0B < 3U) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void Effect_TickOnTimerZero2(void) {
    PartyMember* work;

    BMAGIC_TICK_ON_TIMER_ZERO(2);
}

#include "overlays/bmagic/Effect_DrawFullScreenQuad.h"

MATCH void func_801EF970(void) {
    POLY_F4* prim;
    s32      shade;
    s32      tpage;

    EFFECT_DRAW_FULL_SCREEN_QUAD(3);
}

#include "magic161_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC84(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    func_800AEF98(0xC, 2);
    index  = Battle_AllocEffect(1, 84);
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* row;

        row                     = (BattleWorkImage*)&g_Game.members[active];
        slot                    = &g_BattleEffects[index & BYTE_MASK];
        *(BattleWorkImage*)slot = *row;
    } else {
        BattleWorkImage* row;
        u32              enemy;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        row                     = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *row;
    }
    work                                             = g_Task;
    g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode   = 0;
    g_BattleEffects[index & BYTE_MASK].header.step   = 0;
    g_BattleEffects[index & BYTE_MASK].handler_index = 84;
    g_BattleEffects[index & BYTE_MASK].target.party  = work;
    g_Task->param.unk_0B += 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EEE9C(void) {
    if (g_Task->param.unk_0B == 0) {
        g_BattleEffectBattler->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AEF98(0x18, 0);
        g_Task->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH s32 func_801EEF3C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, g_Task->header.mode);
}

MATCH void func_801EEF80(void) {
    Magic161Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801EF06C(void) {
    u8 count;

    Actor_StepAnimOnce();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        func_800AFC98(2, 4);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0E8(void) {
    u8 count;

    count = g_Task->unk_09;
    if ((count & BYTE_MASK) == 0x10) {
        SND_QueueSelectionFx(0x100);
        g_Task->header.step += 1;
    } else {
        g_Task->unk_09 = count + 4;
    }
    func_801EF1DC();
    Actor_StepAnimOnce();
}

#include "overlays/bmagic/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EF1BC(void) {
    func_801E5988();
}

MATCH void func_801EF1DC(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      red;
    s32      shade;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    prim  = (POLY_G4*)g_GfxPrimCursor;
    red   = g_Task->unk_09 * 12;
    shade = g_Task->unk_09 * 6;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0, 0x13F, 0, 0, 0x78, 0x13F, 0x78);
    setRGB0(prim, 0xC0, 0x60, 0x60);
    setRGB1(prim, 0xC0, 0x60, 0x60);
    setRGB2(prim, red, shade, shade);
    setRGB3(prim, red, shade, shade);
    GFX_AddPrim(1, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0x78, 0x13F, 0x78, 0, 0x167, 0x13F, 0x167);
    setRGB0(prim, red, shade, shade);
    setRGB1(prim, red, shade, shade);
    setRGB2(prim, 0xC0, 0x60, 0x60);
    setRGB3(prim, 0xC0, 0x60, 0x60);
    GFX_AddPrim(1, sizeof(POLY_G4));
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
}

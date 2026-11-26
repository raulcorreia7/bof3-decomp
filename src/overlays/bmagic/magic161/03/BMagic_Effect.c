#include "magic161_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC84(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&TASK(PartyMember)->pos, &g_BattleEffectBattler->pos);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    index  = Battle_AllocEffect(1, 84);
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* image;

        image                   = (BattleWorkImage*)&g_Game.members[active];
        slot                    = &g_BattleEffects[index & BYTE_MASK];
        *(BattleWorkImage*)slot = *image;
    } else {
        BattleWorkImage* image;
        u32              enemy;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        image                   = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *image;
    }
    work                                            = TASK(PartyMember);
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = 84;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    TASK(PartyMember)->param.unk_0B += 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EEE9C(void) {
    if (TASK(PartyMember)->param.unk_0B == 0) {
        g_BattleEffectBattler->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_SelectActiveBattlerScript(0x18, 0);
        TASK(PartyMember)->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH s32 func_801EEF3C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK(PartyMember)->header.mode);
}

MATCH void func_801EEF80(void) {
    Magic161Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801EF06C(void) {
    u8 count;

    Script_AnimStepOnce();
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Battle_PlayActiveBattlerSE(2, 4);
        Battle_MarkDamaged(g_Battle.target_selector);
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF0E8(void) {
    u8 count;

    count = TASK(PartyMember)->unk_09;
    if ((count & BYTE_MASK) == 0x10) {
        SND_SEQueueSelection(0x100);
        TASK(PartyMember)->header.step += 1;
    } else {
        TASK(PartyMember)->unk_09 = count + 4;
    }
    func_801EF1DC();
    Script_AnimStepOnce();
}

#include "overlays/bmagic/shared/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EF1BC(void) {
    Effect_Reset();
}

MATCH void func_801EF1DC(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      red;
    s32      shade;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, tpage);
    prim  = (POLY_G4*)g_GfxPrimCursor;
    red   = TASK(PartyMember)->unk_09 * 12;
    shade = TASK(PartyMember)->unk_09 * 6;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0, 319, 120);
    setRGB0(prim, 0xC0, 0x60, 0x60);
    setRGB1(prim, 0xC0, 0x60, 0x60);
    setRGB2(prim, red, shade, shade);
    setRGB3(prim, red, shade, shade);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0x78, 319, 239);
    setRGB0(prim, red, shade, shade);
    setRGB1(prim, red, shade, shade);
    setRGB2(prim, 0xC0, 0x60, 0x60);
    setRGB3(prim, 0xC0, 0x60, 0x60);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, tpage);
}

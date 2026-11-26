#include "magic004_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC28.h"

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC98(void) {
    PartyMember* battler;
    PartyMember* task;
    PartyMember* owner;
    PartyMember* parent;
    u16*         dst;
    u16*         src;
    u32          slot;
    s32          i;

    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    battler                   = g_BattleEffectBattler;
    task                      = TASK(PartyMember);
    WorldPos_Copy(&task->pos, &battler->pos);
    task->param.unk_0B        = 0;
    TASK(PartyMember)->unk_09 = 0;
    TASK(PartyMember)->header.mode++;
    Battle_SelectActiveBattlerScript(12, 2);
    func_801EF490();
    slot = Battle_AllocEffect(1, 70) & BYTE_MASK;
    Effect_CopyActiveBattlerToSlot(slot);
    owner                              = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].header.step  = 0;
    g_BattleEffects[slot].unk_06       = 1;
    g_BattleEffects[slot].effect_type  = 70;
    g_BattleEffects[slot].target.party = owner;
    TASK(PartyMember)->param.unk_0B++;
    slot                               = Battle_AllocEffect(1, 70) & BYTE_MASK;
    parent                             = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = parent;
    g_BattleEffects[slot].unk_03       = TASK(PartyMember)->unk_03;
    g_BattleEffects[slot].unk_04       = TASK(PartyMember)->unk_04;
    TASK(PartyMember)->param.unk_0B++;
    g_BattleEffectBattler->header.flags |= ACTOR_FLAG_HIDDEN;
    g_Battle.flags |= BATTLE_STATE_DAMAGE_APPLIED;
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++;
    }
    g_GfxPalettePending = 1;
}

MATCH void func_801EEF8C(void) {
    PartyMember* battler;
    u8           selector;

    if (TASK(PartyMember)->param.unk_0B < 2) {
        BMAGIC_SELECT_TARGET_BATTLER();
        TASK(PartyMember)->unk_5D = D_801EFE10[TASK(PartyMember)->unk_04 * 3];
        TASK(PartyMember)->unk_5E = D_801EFE11[TASK(PartyMember)->unk_04 * 3];
        TASK(PartyMember)->unk_5F = D_801EFE12[TASK(PartyMember)->unk_04 * 3];
        GFX_PaletteFreeFadeTarget(battler);
        TASK(PartyMember)->timer = GFX_PaletteAllocFade(battler, (s8)TASK(PartyMember)->unk_5D, (s8)TASK(PartyMember)->unk_5E, (s8)TASK(PartyMember)->unk_5F, 0);
        Battle_SelectActiveBattlerScript(4, 0);
        g_BattleEffectBattler->header.flags &= ~ACTOR_FLAG_HIDDEN;
        Battle_ApplyDamageFlags(LOBU(g_Battle.target_selector), 0x20);
        SND_SEQueueSelection(0x100);
        if ((u32)(g_Battle.action_id - 0x85) < 4) {
            SND_SEQueueSelection(0x101);
        }
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF158(void) {
    u16 cue;

    if (TASK(PartyMember)->param.unk_0B == 0) {
        cue = D_801EFE40[TASK(PartyMember)->unk_04];
        if (cue != 0) {
            SND_SEQueueSelection(cue);
        }
        Battle_MarkDamaged(g_Battle.target_selector);
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->header.mode++;
    }
}

MATCH void func_801EF1F0(void) {
    PartyMember* battler;
    u8           selector;

    if (TASK(PartyMember)->unk_09 < 12) {
        Effect_DrawScreenFade();
        TASK(PartyMember)->unk_09 += 4;
    }
    if ((s8)TASK(PartyMember)->unk_5D != 0) {
        TASK(PartyMember)->unk_5D -= 2;
    }
    if ((s8)TASK(PartyMember)->unk_5E != 0) {
        TASK(PartyMember)->unk_5E -= 2;
    }
    if ((s8)TASK(PartyMember)->unk_5F != 0) {
        TASK(PartyMember)->unk_5F -= 2;
    }
    g_PaletteFades[TASK(PartyMember)->timer].offset.r = TASK(PartyMember)->unk_5D;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g = TASK(PartyMember)->unk_5E;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b = TASK(PartyMember)->unk_5F;
    if ((LOWU(TASK(PartyMember)->unk_5C) & ~0xFF) == 0) {
        BMAGIC_SELECT_TARGET_BATTLER();
        GFX_PaletteFreeFadeTarget(battler);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        TASK(PartyMember)->header.mode++;
    }
}

MATCH void func_801EF3E0(void) {
    u8           slot;
    PartyMember* battler;

    slot = g_Battle.target_selector;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    if (!(Battle_SlotIsBlocked(g_Battle.target_selector) & BYTE_MASK) && battler->header.mode == 6) {
        return;
    }
    g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
    Effect_Reset();
}

MATCH void func_801EF490(void) {
    switch (g_Battle.action_id) {
        case ABILITY_THUNDER_STRIKE:
            TASK(PartyMember)->unk_03 = 0;
            TASK(PartyMember)->unk_04 = 0;
            break;
        case ABILITY_FLAME_STRIKE:
            TASK(PartyMember)->unk_03 = 1;
            TASK(PartyMember)->unk_04 = 1;
            break;
        case ABILITY_MIND_FLAY:
            TASK(PartyMember)->unk_03 = 0;
            TASK(PartyMember)->unk_04 = 2;
            break;
        case ABILITY_WIND_STRIKE:
            TASK(PartyMember)->unk_03 = 1;
            TASK(PartyMember)->unk_04 = 3;
            break;
        case ABILITY_FROST_STRIKE:
            TASK(PartyMember)->unk_03 = 0;
            TASK(PartyMember)->unk_04 = 4;
            break;
        case ABILITY_PYROKINESIS:
            TASK(PartyMember)->unk_03 = 1;
            TASK(PartyMember)->unk_04 = 5;
            break;
        case ABILITY_HOLY_STRIKE:
            TASK(PartyMember)->unk_03 = 0;
            TASK(PartyMember)->unk_04 = 6;
            break;
        /* FAKE: retail bounds the compare tree above ABILITY_HOLY_STRIKE, so one id there shares the default body; the bytes do not say which id, ABILITY_DEMONBANE is the nearest. */
        case ABILITY_DEMONBANE:
        default:
            TASK(PartyMember)->unk_03 = 0;
            TASK(PartyMember)->unk_04 = 7;
            break;
        case ABILITY_FLAME_CLAW:
            TASK(PartyMember)->unk_03 = 1;
            TASK(PartyMember)->unk_04 = 8;
            break;
        case ABILITY_FROST_CLAW:
            TASK(PartyMember)->unk_03 = 1;
            TASK(PartyMember)->unk_04 = 9;
            break;
        case ABILITY_THUNDER_CLAW:
            TASK(PartyMember)->unk_03 = 1;
            TASK(PartyMember)->unk_04 = 10;
            break;
        case ABILITY_SHINING_CLAW:
            TASK(PartyMember)->unk_03 = 1;
            TASK(PartyMember)->unk_04 = 11;
            break;
    }
}

/* func_801EF6E0 */
#include "overlays/bmagic/shared/Effect_DrawScreenFade.h"

/* func_801EF8CC */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF910(void) {
    Magic004TaskSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801EF9E8(void) {
    u8 counter;

    Script_AnimStepOnce();
    counter                   = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        if (g_Battle.action_id > 0x84) {
            Battle_PlayActiveBattlerSE(2, 4);
        } else {
            Battle_PlayActiveBattlerSE(0, 4);
        }
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EFAD4(void) {
    Effect_Reset();
}

/* func_801EFAF4 */
#include "overlays/bmagic/shared/BMagic_RunStep.h"

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderTwo.h"

MATCH void func_801EFBEC(void) {
    PartyMember* work;

    work                      = TASK(PartyMember);
    work->pos.x.fixed         = g_Battle.selected_actor->pos.x.fixed;
    work->pos.y.fixed         = g_Battle.selected_actor->pos.y.fixed;
    work->pos.z.fixed         = g_Battle.selected_actor->pos.z.fixed + 0x800000;
    TASK(PartyMember)->unk_25 = 0x1D;
    TASK(PartyMember)->unk_26 = 0;
    if (TASK(PartyMember)->unk_03 != 0) {
        TASK(PartyMember)->unk_27 = 0x1A;
        TASK(PartyMember)->unk_28 = 1;
        TASK(PartyMember)->unk_24 = 0;
    } else {
        TASK(PartyMember)->unk_27 = 0xA0;
        TASK(PartyMember)->unk_28 = 0;
        TASK(PartyMember)->unk_24 = 4;
    }
    TASK(PartyMember)->unk_5D       = 0;
    TASK(PartyMember)->unk_5E       = 0;
    TASK(PartyMember)->unk_5F       = 0;
    TASK(PartyMember)->unk_5C       = 0;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 4;
    TASK(PartyMember)->unk_2C.value = 0;
    TASK(PartyMember)->unk_2B       = 1;
    Script_Select(0);
    TASK(PartyMember)->unk_09 = D_801EFE34[TASK(PartyMember)->unk_04];
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EFD84(void) {
    u8 count;

    count = TASK(PartyMember)->unk_09;
    if (count != 0) {
        count -= 1;
        TASK(PartyMember)->unk_09 = count;
        if (!(count & BYTE_MASK)) {
            SND_SEQueueSelection(0x101);
        }
    }
    if (Script_AnimStepOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
        return;
    }
    Area_AddGridActor();
}

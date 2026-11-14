#include "magic004_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

#include "overlays/bmagic/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC98(void) {
    PartyMember* battler;
    PartyMember* task;
    PartyMember* owner;
    PartyMember* parent;
    u16*         dst;
    u16*         src;
    u32          slot;
    s32          i;

    g_Task->facing = g_BattleEffectBattler->facing;
    battler        = g_BattleEffectBattler;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &battler->pos);
    task->param.unk_0B = 0;
    g_Task->unk_09     = 0;
    g_Task->header.mode++;
    func_800AEF98(12, 2);
    func_801EF490();
    slot = Battle_AllocEffect(1, 70) & BYTE_MASK;
    Effect_CopyActiveBattlerToSlot(slot);
    owner                               = g_Task;
    g_BattleEffects[slot].header.mode   = 0;
    g_BattleEffects[slot].header.step   = 0;
    g_BattleEffects[slot].unk_06        = 1;
    g_BattleEffects[slot].handler_index = 70;
    g_BattleEffects[slot].target.party  = owner;
    g_Task->param.unk_0B++;
    slot                               = Battle_AllocEffect(1, 70) & BYTE_MASK;
    parent                             = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = parent;
    g_BattleEffects[slot].unk_03       = g_Task->unk_03;
    g_BattleEffects[slot].unk_04       = g_Task->unk_04;
    g_Task->param.unk_0B++;
    g_BattleEffectBattler->header.flags |= ACTOR_FLAG_HIDDEN;
    g_Battle.state |= BATTLE_STATE_DAMAGE_APPLIED;
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        *dst++ = *src++;
    }
    g_GfxPalettePending = 1;
}

MATCH void func_801EEF8C(void) {
    PartyMember* battler;
    u8           selector;

    if (g_Task->param.unk_0B < 2) {
        BMAGIC_SELECT_TARGET_BATTLER();
        g_Task->unk_5D = D_801EFE10[g_Task->unk_04 * 3];
        g_Task->unk_5E = D_801EFE11[g_Task->unk_04 * 3];
        g_Task->unk_5F = D_801EFE12[g_Task->unk_04 * 3];
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer = GFX_AllocPaletteFade(battler, (s8)g_Task->unk_5D, (s8)g_Task->unk_5E, (s8)g_Task->unk_5F, 0);
        func_800AEF98(4, 0);
        g_BattleEffectBattler->header.flags &= ~ACTOR_FLAG_HIDDEN;
        Battle_ApplyDamageFlags(LOBU(g_Battle.target_selector), 0x20);
        SND_QueueSelectionEffect(0x100);
        if ((u32)(g_Battle.action_id - 0x85) < 4) {
            SND_QueueSelectionEffect(0x101);
        }
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF158(void) {
    u16 cue;

    if (g_Task->param.unk_0B == 0) {
        cue = D_801EFE40[g_Task->unk_04];
        if (cue != 0) {
            SND_QueueSelectionEffect(cue);
        }
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 0;
        g_Task->header.mode++;
    }
}

MATCH void func_801EF1F0(void) {
    PartyMember* battler;
    u8           selector;

    if (g_Task->unk_09 < 12) {
        Effect_DrawScreenFade();
        g_Task->unk_09 += 4;
    }
    if ((s8)g_Task->unk_5D != 0) {
        g_Task->unk_5D -= 2;
    }
    if ((s8)g_Task->unk_5E != 0) {
        g_Task->unk_5E -= 2;
    }
    if ((s8)g_Task->unk_5F != 0) {
        g_Task->unk_5F -= 2;
    }
    g_PaletteFades[g_Task->timer].offset.red   = g_Task->unk_5D;
    g_PaletteFades[g_Task->timer].offset.green = g_Task->unk_5E;
    g_PaletteFades[g_Task->timer].offset.blue  = g_Task->unk_5F;
    if ((LOWU(g_Task->unk_5C) & ~0xFF) == 0) {
        BMAGIC_SELECT_TARGET_BATTLER();
        GFX_FreePaletteFadeTarget(battler);
        func_800AF814(g_Battle.target_selector);
        g_Task->header.mode++;
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
    g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
    func_801E5988();
}

MATCH void func_801EF490(void) {
    switch (g_Battle.action_id) {
        case ABILITY_THUNDER_STRIKE:
            g_Task->unk_03 = 0;
            g_Task->unk_04 = 0;
            break;
        case ABILITY_FLAME_STRIKE:
            g_Task->unk_03 = 1;
            g_Task->unk_04 = 1;
            break;
        case ABILITY_MIND_FLAY:
            g_Task->unk_03 = 0;
            g_Task->unk_04 = 2;
            break;
        case ABILITY_WIND_STRIKE:
            g_Task->unk_03 = 1;
            g_Task->unk_04 = 3;
            break;
        case ABILITY_FROST_STRIKE:
            g_Task->unk_03 = 0;
            g_Task->unk_04 = 4;
            break;
        case ABILITY_PYROKINESIS:
            g_Task->unk_03 = 1;
            g_Task->unk_04 = 5;
            break;
        case ABILITY_HOLY_STRIKE:
            g_Task->unk_03 = 0;
            g_Task->unk_04 = 6;
            break;
        /* FAKE: retail bounds the compare tree above ABILITY_HOLY_STRIKE, so one id there shares the default body; the bytes do not say which id, ABILITY_DEMONBANE is the nearest. */
        case ABILITY_DEMONBANE:
        default:
            g_Task->unk_03 = 0;
            g_Task->unk_04 = 7;
            break;
        case ABILITY_FLAME_CLAW:
            g_Task->unk_03 = 1;
            g_Task->unk_04 = 8;
            break;
        case ABILITY_FROST_CLAW:
            g_Task->unk_03 = 1;
            g_Task->unk_04 = 9;
            break;
        case ABILITY_THUNDER_CLAW:
            g_Task->unk_03 = 1;
            g_Task->unk_04 = 10;
            break;
        case ABILITY_SHINING_CLAW:
            g_Task->unk_03 = 1;
            g_Task->unk_04 = 11;
            break;
    }
}

/* func_801EF6E0 */
#include "overlays/bmagic/Effect_DrawScreenFade.h"

/* func_801EF8CC */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF910(void) {
    Magic004Steps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

INCLUDE_ASM(func_801EF9E8);

#include "overlays/bmagic/Effect_LowerTickerStepOnReady.h"

MATCH void func_801EFAD4(void) {
    func_801E5988();
}

/* func_801EFAF4 */
#include "overlays/bmagic/BMagic_RunStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

MATCH void func_801EFBEC(void) {
    PartyMember* work;

    work              = g_Task;
    work->pos.x.fixed = g_Battle.selected_actor->pos.x.fixed;
    work->pos.y.fixed = g_Battle.selected_actor->pos.y.fixed;
    work->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed + 0x800000;
    g_Task->unk_25    = 0x1D;
    g_Task->unk_26    = 0;
    if (g_Task->unk_03 != 0) {
        g_Task->unk_27 = 0x1A;
        g_Task->unk_28 = 1;
        g_Task->unk_24 = 0;
    } else {
        g_Task->unk_27 = 0xA0;
        g_Task->unk_28 = 0;
        g_Task->unk_24 = 4;
    }
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_5C      = 0;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 1;
    Actor_SelectScript(0);
    g_Task->unk_09 = D_801EFE34[g_Task->unk_04];
    g_Task->header.step += 1;
}

MATCH void func_801EFD84(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        count -= 1;
        g_Task->unk_09 = count;
        if (!(count & BYTE_MASK)) {
            SND_QueueSelectionEffect(0x101);
        }
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
        return;
    }
    func_8014D290();
}

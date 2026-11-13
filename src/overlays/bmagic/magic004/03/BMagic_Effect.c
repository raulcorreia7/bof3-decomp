#include "magic004_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

INCLUDE_ASM(func_801EEC98);

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
        SND_QueueSelectionFx(0x100);
        if ((u32)(g_Battle.action_id - 0x85) < 4) {
            SND_QueueSelectionFx(0x101);
        }
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF158(void) {
    u16 cue;

    if (g_Task->param.unk_0B == 0) {
        cue = D_801EFE40[g_Task->unk_04];
        if (cue != 0) {
            SND_QueueSelectionFx(cue);
        }
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 0;
        g_Task->header.mode++;
    }
}

INCLUDE_ASM(func_801EF1F0);

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

INCLUDE_ASM(func_801EF490);

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
            SND_QueueSelectionFx(0x101);
        }
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
        return;
    }
    func_8014D290();
}

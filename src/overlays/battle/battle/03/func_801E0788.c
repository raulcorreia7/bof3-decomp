#include "battle_03.h"

MATCH void func_801E0788(void) {
    PartyBattler* w;
    PartyBattler* w2;
    u32           flags;
    s32           i;
    u16*          half;
    u16*          half2;

    func_801DDFEC(g_SpadWork->slot);
    func_801DD14C(g_SpadWork->slot);
    w = g_GameState;
    if (w->flags_124.value & 4) {
        g_SpadWork->word_08.byte.unk_09 = 30;
        g_SpadWork->unk_03              = 1;
        g_SpadWork->unk_04              = 0;
    } else if (w->flags_128.value & 2) {
        half = &g_BattleState;
        if ((*half & 0x4000) && (D_801463CA == g_SpadWork->slot)) {
            *half &= 0xBFFF;
        }
        g_SpadWork->unk_03 = 4;
    } else if (w->stats.accessories[0] == ACCESSORY_SOUL_GEM) {
        g_Characters[w->unk_13A[2]].accessories[0] = ACCESSORY_NOTHING;
        g_SpadWork->word_08.byte.unk_09            = 30;
        g_SpadWork->unk_03                         = 3;
    } else if (w->stats.accessories[1] == ACCESSORY_SOUL_GEM) {
        g_Characters[w->unk_13A[2]].accessories[1] = ACCESSORY_NOTHING;
        g_SpadWork->word_08.byte.unk_09            = 30;
        g_SpadWork->unk_03                         = 6;
    } else if (w->stats.armor == ARMOR_MANLY_CLOTHES) {
        g_Characters[w->unk_13A[2]].armor = ARMOR_NOTHING;
        g_SpadWork->word_08.byte.unk_09   = 30;
        g_SpadWork->unk_03                = 5;
    } else {
        VOL(u8, g_BattleLivingPartyCount) -= 1;
        for (i = 0; (u8)i < 8; i++) {
            g_GameState->unk_12C[(u8)i] = 0;
        }
        w2              = g_GameState;
        w2->counter_121 = 0;
        w2->flags_128.value &= 0xFFFB84FF;
        g_GameState->counter_136 = 0;
        g_GameState->counter_137 = 0;
        g_GameState->charge      = 0;
        g_GameState->unk_139     = 0;
        func_800A9BD8(g_SpadWork->slot);
        if ((func_801E0E0C() & BYTE_MASK) || (g_BattleLivingPartyCount == 0)) {
            VOL(u8, g_BattleResult) |= BATTLE_RESULT_DEFEAT;
        }
        half2 = &g_BattleState;
        if ((*half2 & 0x4000) && (D_801463CA == g_SpadWork->slot)) {
            *half2 &= 0xBFFF;
        }
        if (g_GameState->flags_128.value & 1) {
            g_SpadWork->unk_03 = 4;
        } else {
            Battle_ClearSlotPending(g_SpadWork->slot);
            w                   = g_GameState;
            flags               = w->flags_124.value & ~0x70;
            w->flags_124.value  = flags & ~0x200;
            g_SpadWork->step_01 = 3;
            g_SpadWork->unk_02  = 0;
            g_SpadWork->unk_03  = 0;
        }
    }
    func_801DEDE4();
}

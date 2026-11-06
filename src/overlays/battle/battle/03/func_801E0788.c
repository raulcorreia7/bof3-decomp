#include "battle_03.h"

MATCH void func_801E0788(void) {
    PartyBattler* w;
    PartyBattler* w2;
    u32           flags;
    s32           i;
    u16*          half;
    u16*          half2;

    func_801DDFEC(g_Task->slot);
    func_801DD14C(g_Task->slot);
    w = g_GameState;
    if (w->turn.damage_flags.value & 4) {
        g_Task->unk_09 = 30;
        g_Task->unk_03 = 1;
        g_Task->unk_04 = 0;
    } else if (w->turn.action_flags.value & 2) {
        half = &g_BattleState;
        if ((*half & 0x4000) && (D_801463CA == g_Task->slot)) {
            *half &= 0xBFFF;
        }
        g_Task->unk_03 = 4;
    } else if (w->chr.equip.accessories[0] == ACCESSORY_SOUL_GEM) {
        g_Characters[w->unk_13A[2]].equip.accessories[0] = ACCESSORY_NOTHING;
        g_Task->unk_09                                   = 30;
        g_Task->unk_03                                   = 3;
    } else if (w->chr.equip.accessories[1] == ACCESSORY_SOUL_GEM) {
        g_Characters[w->unk_13A[2]].equip.accessories[1] = ACCESSORY_NOTHING;
        g_Task->unk_09                                   = 30;
        g_Task->unk_03                                   = 6;
    } else if (w->chr.equip.armor == ARMOR_MANLY_CLOTHES) {
        g_Characters[w->unk_13A[2]].equip.armor = ARMOR_NOTHING;
        g_Task->unk_09                          = 30;
        g_Task->unk_03                          = 5;
    } else {
        VOL(u8, g_BattleLivingPartyCount) -= 1;
        for (i = 0; (u8)i < 8; i++) {
            g_GameState->unk_12C[(u8)i] = 0;
        }
        w2               = g_GameState;
        w2->turn.counter = 0;
        w2->turn.action_flags.value &= 0xFFFB84FF;
        g_GameState->counter_136   = 0;
        g_GameState->counter_137   = 0;
        g_GameState->focus_counter = 0;
        g_GameState->unk_139       = 0;
        func_800A9BD8(g_Task->slot);
        if ((func_801E0E0C() & BYTE_MASK) || (g_BattleLivingPartyCount == 0)) {
            VOL(u8, g_BattleResult) |= BATTLE_RESULT_DEFEAT;
        }
        half2 = &g_BattleState;
        if ((*half2 & 0x4000) && (D_801463CA == g_Task->slot)) {
            *half2 &= 0xBFFF;
        }
        if (g_GameState->turn.action_flags.value & 1) {
            g_Task->unk_03 = 4;
        } else {
            Battle_ClearSlotPending(g_Task->slot);
            w                          = g_GameState;
            flags                      = w->turn.damage_flags.value & ~0x70;
            w->turn.damage_flags.value = flags & ~0x200;
            g_Task->header.mode        = 3;
            g_Task->header.step        = 0;
            g_Task->unk_03             = 0;
        }
    }
    func_801DEDE4();
}

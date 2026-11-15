#include "battle_03.h"

MATCH void func_801E0788(void) {
    PartyMember* w;
    PartyMember* w2;
    u32          flags;
    s32          i;
    u16*         half;
    u16*         half2;

    Battle_GetTurnCursor(g_Task->slot);
    Battle_CancelTurn(g_Task->slot);
    w = g_Game.current;
    if (w->u.turn.damage_flags.value & COMBATANT_FLAG_WILLPOWER_SURVIVED) {
        g_Task->unk_09 = 30;
        g_Task->unk_03 = 1;
        g_Task->unk_04 = 0;
    } else if (w->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM) {
        half = &g_Battle.state;
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
        VOL(u8, g_Battle.living_party_count) -= 1;
        for (i = 0; (u8)i < 8; i++) {
            g_Game.current->status.unk_12C[(u8)i] = 0;
        }
        w2                 = g_Game.current;
        w2->u.turn.counter = 0;
        w2->u.turn.action_flags.value &= ~(COMBATANT_FLAG_ALWAYS_HITS | COMBATANT_FLAG_DAMAGE_HALVED | COMBATANT_FLAG_HOLY_RESIST_ZERO | COMBATANT_FLAG_SELECTION_BONUS |
                                           COMBATANT_FLAG_FIRE_RESIST_ZERO | COMBATANT_FLAG_CHARGING | COMBATANT_FLAG_SELECTED);
        g_GameState->counter_136      = 0;
        g_Game.current->counter_137   = 0;
        g_Game.current->focus_counter = 0;
        g_Game.current->unk_139       = 0;
        Battle_RescaleStats(g_Task->slot);
        if ((func_801E0E0C() & BYTE_MASK) || (g_Battle.living_party_count == 0)) {
            VOL(u8, g_Battle.outcome.result) |= BATTLE_RESULT_DEFEAT;
        }
        half2 = &g_Battle.state;
        if ((*half2 & 0x4000) && (D_801463CA == g_Task->slot)) {
            *half2 &= 0xBFFF;
        }
        if (g_Game.current->u.turn.action_flags.value & COMBATANT_FLAG_DRAGON_FORM_QUEUED) {
            g_Task->unk_03 = 4;
        } else {
            Battle_ClearSlotPending(g_Task->slot);
            w                            = g_Game.current;
            flags                        = w->u.turn.damage_flags.value & ~(COMBATANT_FLAG_UNK_4 | COMBATANT_FLAG_UNK_5 | COMBATANT_FLAG_DAMAGED);
            w->u.turn.damage_flags.value = flags & ~0x200;
            g_Task->header.mode          = 3;
            g_Task->header.step          = 0;
            g_Task->unk_03               = 0;
        }
    }
    func_801DEDE4();
}

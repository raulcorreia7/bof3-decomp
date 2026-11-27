#include "battle_03.h"

MATCH void func_801E0788(void) {
    PartyMember* w;
    PartyMember* w2;
    u32          flags;
    s32          i;
    u16*         half;
    u16*         half2;

    Battle_GetTurnCursor(SELF(PartyMember)->slot);
    Battle_CancelTurn(SELF(PartyMember)->slot);
    w = g_Game.current;
    if (w->u.turn.damage_flags.value & BATTLER_DAMAGE_WILLPOWER_SURVIVED) {
        SELF(PartyMember)->unk_09 = 30;
        SELF(PartyMember)->unk_03 = 1;
        SELF(PartyMember)->unk_04 = 0;
    } else if (w->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM) {
        half = &g_Battle.flags;
        if ((*half & 0x4000) && (g_Battle.unk_EA[0] == SELF(PartyMember)->slot)) {
            *half &= 0xBFFF;
        }
        SELF(PartyMember)->unk_03 = 4;
    } else if (w->chr.equip.accessories[0] == ACCESSORY_SOUL_GEM) {
        g_Characters[w->unk_13A[2]].equip.accessories[0] = ACCESSORY_NOTHING;
        SELF(PartyMember)->unk_09                        = 30;
        SELF(PartyMember)->unk_03                        = 3;
    } else if (w->chr.equip.accessories[1] == ACCESSORY_SOUL_GEM) {
        g_Characters[w->unk_13A[2]].equip.accessories[1] = ACCESSORY_NOTHING;
        SELF(PartyMember)->unk_09                        = 30;
        SELF(PartyMember)->unk_03                        = 6;
    } else if (w->chr.equip.armor == ARMOR_MANLY_CLOTHES) {
        g_Characters[w->unk_13A[2]].equip.armor = ARMOR_NOTHING;
        SELF(PartyMember)->unk_09               = 30;
        SELF(PartyMember)->unk_03               = 5;
    } else {
        g_Battle.living_party_count -= 1;
        for (i = 0; (u8)i < 8; i++) {
            g_Game.current->status.unk_12C[(u8)i] = 0;
        }
        w2                 = g_Game.current;
        w2->u.turn.counter = 0;
        w2->u.turn.action_flags.value &= ~(BATTLER_ACTION_ALWAYS_HITS | BATTLER_ACTION_DAMAGE_HALVED | BATTLER_ACTION_HOLY_RESIST_ZERO | BATTLER_ACTION_SELECTION_BONUS |
                                           BATTLER_ACTION_FIRE_RESIST_ZERO | BATTLER_ACTION_CHARGING | BATTLER_ACTION_SELECTED);
        g_GameState->charge_counter    = 0;
        g_Game.current->status_counter = 0;
        g_Game.current->focus_counter  = 0;
        g_Game.current->unk_139        = 0;
        Battle_RescaleStats(SELF(PartyMember)->slot);
        if ((func_801E0E0C() & BYTE_MASK) || (g_Battle.living_party_count == 0)) {
            g_Battle.outcome.result |= BATTLE_RESULT_DEFEAT;
        }
        half2 = &g_Battle.flags;
        if ((*half2 & 0x4000) && (g_Battle.unk_EA[0] == SELF(PartyMember)->slot)) {
            *half2 &= 0xBFFF;
        }
        if (g_Game.current->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) {
            SELF(PartyMember)->unk_03 = 4;
        } else {
            Battle_ClearSlotPending(SELF(PartyMember)->slot);
            w                              = g_Game.current;
            flags                          = w->u.turn.damage_flags.value & ~(BATTLER_DAMAGE_UNK_4 | BATTLER_DAMAGE_UNK_5 | BATTLER_DAMAGE_TAKEN);
            w->u.turn.damage_flags.value   = flags & ~0x200;
            SELF(PartyMember)->header.mode = 3;
            SELF(PartyMember)->header.step = 0;
            SELF(PartyMember)->unk_03      = 0;
        }
    }
    func_801DEDE4();
}

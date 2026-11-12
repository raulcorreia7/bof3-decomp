#include "battle_15.h"

MATCH void func_800A68A4(void) {
    volatile u8* battler;
    u8           i;
    u8           slot;
    u8           index;
    u32          flags;

    i = 0;
    {
        /* The loop's pointer must die before the first call, or the address is
         * held in s1 from entry. */
        volatile u8* loop_battler = &g_Battle.active_battler;
        for (; i < 8; i++) {
            g_Game.members[*loop_battler].status.unk_12C[i] = 0;
        }
    }
    battler = &g_Battle.active_battler;
    g_Game.members[*battler].u.turn.damage_flags.volatile_value &= ~(COMBATANT_FLAG_REPRISAL | COMBATANT_FLAG_DAMAGE_IMMUNE);
    g_Game.members[*battler].u.turn.action_flags.volatile_value &= ~(COMBATANT_FLAG_ALWAYS_HITS | COMBATANT_FLAG_DAMAGE_HALVED | COMBATANT_FLAG_HOLY_RESIST_ZERO | COMBATANT_FLAG_SELECTION_BONUS |
                                                                     COMBATANT_FLAG_FIRE_RESIST_ZERO | COMBATANT_FLAG_CHARGING | COMBATANT_FLAG_SELECTED);
    Battle_RescaleStats(*battler);
    index                                                    = *battler;
    flags                                                    = g_Game.members[index].u.turn.action_flags.volatile_value;
    D_800B6F58                                               = 0;
    D_800B6F5C                                               = 0;
    g_Game.members[index].u.turn.action_flags.volatile_value = flags | COMBATANT_FLAG_DRAGON_FORM;
    slot                                                     = func_800A6C2C();
    if (slot != GAME_NONE) {
        func_800A7C14(slot);
        D_800B6F58 = slot + 4;
        if ((u8)(slot + 4) == DRAGON_FORM_BERSERK_KAISER) {
            g_Game.members[*battler].u.turn.action_flags.value |= COMBATANT_FLAG_DRAGON_FORM_BERSERK;
        }
        if (D_800B6F58 == DRAGON_FORM_FAILURE_KAISER) {
            g_Game.members[*battler].u.turn.action_flags.value |= COMBATANT_FLAG_DRAGON_FORM_CONTROLLED;
        }
        if (D_800B6F58 == DRAGON_FORM_TRUE_KAISER) {
            g_Game.members[*battler].u.turn.action_flags.value |= COMBATANT_FLAG_DRAGON_FORM_CONTROLLED;
        }
    } else {
        func_800A6E14(0xFF);
    }
    i = 5;
    for (; i != 0; i--) {
        g_BattleTargetRows[i].slot_00 = g_BattleTargetRows[i - 1].slot_00;
        g_BattleTargetRows[i].slot_01 = g_BattleTargetRows[i - 1].slot_01;
        g_BattleTargetRows[i].slot_02 = g_BattleTargetRows[i - 1].slot_02;
        g_BattleTargetRows[i].gate_03 = g_BattleTargetRows[i - 1].gate_03;
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        FIELD(u8, &g_BattleTargetRows, i) = g_Battle.genes[i];
    }
    for (; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        FIELD(u8, &g_BattleTargetRows, i) = 0xFF;
    }
    g_BattleTargetRows[0].gate_03 = (D_800B6F5C << 5) + (D_800B6F58 & 0x1F);
    g_Battle.dragon_form          = D_800B6F58;
    D_801463B9                    = D_800B6F5C;
    Battle_RescaleStats(g_Battle.active_battler);
}

#include "battle_15.h"

/* Applies the queued hit's HP and AP changes to the target and runs the hit's effect handler. */
MATCH void func_8009D198(void) {
    u8  effect;
    u16 action_word;

    if (BATTLER_IS_PLAYER(g_Battle.target)) {
        g_Game.members[g_Battle.target].u.turn.target_flags |= BATTLE_HIT_HP | BATTLE_HIT_HP_LANDED | BATTLE_HIT_AP_LANDED;
    } else {
        ENEMY_COMBATANT(g_Battle.target).turn.target_flags |= BATTLE_HIT_HP | BATTLE_HIT_HP_LANDED | BATTLE_HIT_AP_LANDED;
    }

    if (g_Battle.action_type != BATTLE_ACTION_ABILITY || g_Battle.action_id != ABILITY_MEDITATION) {
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            if (g_Game.members[g_Battle.active_battler].u.turn.action_flags.value & BATTLER_ACTION_MEDITATION) {
                {
                    volatile u16* p = &D_801EC312;
                    *p              = *p * (g_Game.members[g_Battle.active_battler].unk_139 + 1);
                }
                g_Game.members[g_Battle.active_battler].unk_139 = 0;
                g_Game.members[g_Battle.active_battler].u.turn.action_flags.value &= ~BATTLER_ACTION_MEDITATION;
            }
        } else if (ENEMY_COMBATANT(g_Battle.active_battler).turn.action_flags.value & BATTLER_ACTION_MEDITATION) {
            {
                volatile u16* p = &D_801EC312;
                *p              = *p * (ENEMY_COMBATANT(g_Battle.active_battler).unk_115 + 1);
            }
            ENEMY_COMBATANT(g_Battle.active_battler).unk_115 = 0;
            ENEMY_COMBATANT(g_Battle.active_battler).turn.action_flags.value &= ~BATTLER_ACTION_MEDITATION;
        }
    }

    if (g_Battle.action_type == BATTLE_ACTION_ABILITY) {
        effect = g_BattleAbilityEffectIds[(u16)g_Battle.action_id];
    } else {
        action_word = g_Battle.action->unk_02;
        effect      = D_800B470C[action_word >> 8][(u8)action_word];
    }
    g_BattleItemEffects[effect]();

    if (BATTLER_IS_PLAYER(g_Battle.target)) {
        if (g_Game.members[g_Battle.target].u.turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
            g_Battle.target_record->hp_change = 0;
            g_Battle.target_record->ap_change = 0;
        }
    } else if (ENEMY_COMBATANT(g_Battle.target).turn.damage_flags.value & BATTLER_DAMAGE_IMMUNE) {
        g_Battle.target_record->hp_change = 0;
        g_Battle.target_record->ap_change = 0;
    }

    if (g_Battle.target_record->hp_change >= 10000) {
        g_Battle.target_record->hp_change = 9999;
    }
    if (g_Battle.target_record->hp_change < -9999) {
        g_Battle.target_record->hp_change = -9999;
    }
        if (g_Battle.target_record->hp_change != 0) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (g_Battle.target_record->hp_change > 0) {
                if (g_Battle.target_record->hp_change < g_Game.members[g_Battle.target].chr.hp) {
                    g_Game.members[g_Battle.target].chr.hp -= g_Battle.target_record->hp_change;
                } else {
                    if (g_Battle.target_record->hp_change - g_Game.members[g_Battle.target].chr.hp < g_Game.members[g_Battle.target].chr.willpower) {
                        if (!(g_Game.members[g_Battle.target].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM_QUEUED) &&
                            !(g_Game.members[g_Battle.target].u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM)) {
                            g_Game.members[g_Battle.target].u.turn.damage_flags.value |= BATTLER_DAMAGE_WILLPOWER_SURVIVED;
                        }
                    }
                    g_Game.members[g_Battle.target].chr.hp = 0;
                }
            } else if (g_Game.members[g_Battle.target].chr.hp - g_Battle.target_record->hp_change < g_Game.members[g_Battle.target].chr.stats.max_hp) {
                g_Game.members[g_Battle.target].chr.hp -= g_Battle.target_record->hp_change;
            } else {
                g_Game.members[g_Battle.target].chr.hp = g_Game.members[g_Battle.target].chr.stats.max_hp;
                g_Game.members[g_Battle.target].u.turn.target_flags |= BATTLE_HIT_HP | BATTLE_HIT_HP_MAX;
                g_Game.members[g_Battle.target].u.turn.target_flags &= ~BATTLE_HIT_HP_LANDED;
            }
        } else if (ENEMY_COMBATANT(g_Battle.target).hp != 0xFFFF) {
            if (g_Battle.target_record->hp_change > 0) {
                if (g_Battle.target_record->hp_change < ENEMY_COMBATANT(g_Battle.target).hp) {
                    ENEMY_COMBATANT(g_Battle.target).hp -= g_Battle.target_record->hp_change;
                } else {
                    ENEMY_COMBATANT(g_Battle.target).hp = 0;
                }
            } else if (ENEMY_COMBATANT(g_Battle.target).hp - g_Battle.target_record->hp_change < ENEMY_COMBATANT(g_Battle.target).stats.max_hp) {
                ENEMY_COMBATANT(g_Battle.target).hp -= g_Battle.target_record->hp_change;
            } else {
                ENEMY_COMBATANT(g_Battle.target).hp = ENEMY_COMBATANT(g_Battle.target).stats.max_hp;
                ENEMY_COMBATANT(g_Battle.target).turn.target_flags |= BATTLE_HIT_HP | BATTLE_HIT_HP_MAX;
                ENEMY_COMBATANT(g_Battle.target).turn.target_flags &= ~BATTLE_HIT_HP_LANDED;
            }
        }
    }

    if (g_Battle.target_record->ap_change >= 10000) {
        g_Battle.target_record->ap_change = 9999;
    }
    if (g_Battle.target_record->ap_change < -9999) {
        g_Battle.target_record->ap_change = -9999;
    }
        if (g_Battle.target_record->ap_change != 0) {
        if (BATTLER_IS_PLAYER(g_Battle.target)) {
            if (g_Battle.target_record->ap_change > 0) {
                if (g_Battle.target_record->ap_change < g_Game.members[g_Battle.target].chr.ap) {
                    g_Game.members[g_Battle.target].chr.ap -= g_Battle.target_record->ap_change;
                } else {
                    g_Game.members[g_Battle.target].chr.ap = 0;
                }
            } else if (g_Game.members[g_Battle.target].chr.ap - g_Battle.target_record->ap_change < g_Game.members[g_Battle.target].chr.stats.max_ap) {
                g_Game.members[g_Battle.target].chr.ap -= g_Battle.target_record->ap_change;
            } else {
                g_Game.members[g_Battle.target].chr.ap = g_Game.members[g_Battle.target].chr.stats.max_ap;
                g_Game.members[g_Battle.target].u.turn.target_flags |= BATTLE_HIT_AP | BATTLE_HIT_AP_MAX;
                g_Game.members[g_Battle.target].u.turn.target_flags &= ~BATTLE_HIT_AP_LANDED;
            }
        } else if (ENEMY_COMBATANT(g_Battle.target).ap != 0xFFFF) {
            if (g_Battle.target_record->ap_change > 0) {
                if (g_Battle.target_record->ap_change < ENEMY_COMBATANT(g_Battle.target).ap) {
                    ENEMY_COMBATANT(g_Battle.target).ap -= g_Battle.target_record->ap_change;
                } else {
                    ENEMY_COMBATANT(g_Battle.target).ap = 0;
                }
            } else if (ENEMY_COMBATANT(g_Battle.target).ap - g_Battle.target_record->ap_change < ENEMY_COMBATANT(g_Battle.target).stats.max_hp) {
                /* Retail compares the AP overflow against max_hp, not max_ap. */
                ENEMY_COMBATANT(g_Battle.target).ap -= g_Battle.target_record->ap_change;
            } else {
                ENEMY_COMBATANT(g_Battle.target).ap = ENEMY_COMBATANT(g_Battle.target).stats.max_ap;
                ENEMY_COMBATANT(g_Battle.target).turn.target_flags |= BATTLE_HIT_AP | BATTLE_HIT_AP_MAX;
                ENEMY_COMBATANT(g_Battle.target).turn.target_flags &= ~BATTLE_HIT_AP_LANDED;
            }
        }
    }
}

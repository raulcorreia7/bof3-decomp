#include "battle_15.h"

/* Applies the status bits named by status_mask to one battler (players below 3,
 * enemies from 3): each bit is set in g_Battle.pending_status unless the battler already has
 * it or a blocking status, then the merged word is stored back and published. */
/* func_800A31E0 */
MATCH void Battle_AddStatus(u8 battler_index, u16 status_mask) {
    u16  status;
    u8   slot;
    u32  merged;
    u16* acc;

    if (battler_index < 3) {
        status = g_Game.members[battler_index].chr.status;
    } else {
        status = ENEMY_COMBATANT(battler_index).status;
    }
    if ((status_mask & STATUS_POISONED) && !(status & STATUS_POISONED)) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_POISONED;
    }
    if ((status_mask & STATUS_UNK_0) && !(status & STATUS_UNK_0)) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_UNK_0;
    }
    if ((status_mask & STATUS_UNK_1) && !(status & STATUS_UNK_1)) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_UNK_1;
    }
    if (status_mask & STATUS_SLEEPING) {
        if (func_800A3638(battler_index, 6) & BYTE_MASK) {
            if (!(status & (STATUS_UNK_11 | STATUS_SLEEPING))) {
                Battle_CureStatus(battler_index, 0x38);
                acc = &g_Battle.pending_status;
                *acc |= STATUS_SLEEPING;
                func_801DDFEC(battler_index);
                func_801DD14C(battler_index);
            }
        }
    }
    if ((status_mask & STATUS_CONFUSED) && (func_800A3638(battler_index, 8) & BYTE_MASK) && !(status & (STATUS_UNK_11 | STATUS_SLEEPING | STATUS_CONFUSED | STATUS_PARALYZED))) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_CONFUSED;
        func_801DDFEC(battler_index);
        g_BattleEffects[battler_index].arg.sway = 0;
        if (battler_index < 3) {
            g_Game.members[battler_index].u.turn.command.type = 0;
            g_Game.members[battler_index].u.turn.damage_flags.volatile_value &= ~2;
            g_Game.members[battler_index].u.turn.action_flags.volatile_value &= ~4;
        } else {
            ENEMY_COMBATANT(battler_index).turn.command.type = 0;
            ENEMY_COMBATANT(battler_index).turn.damage_flags.value &= ~2;
        }
    }
    if ((status_mask & STATUS_BLIND) && (func_800A3638(battler_index, 9) & BYTE_MASK) && (func_800A36BC(battler_index, 0x2B) & BYTE_MASK) &&
        !(status & (STATUS_UNK_11 | STATUS_BLIND | STATUS_PARALYZED))) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_BLIND;
    }
    if ((status_mask & STATUS_SILENCED) && !(status & (STATUS_UNK_11 | STATUS_SILENCED | STATUS_PARALYZED))) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_SILENCED;
    }
    if ((status_mask & STATUS_PARALYZED) && !(status & (STATUS_UNK_11 | STATUS_PARALYZED))) {
        Battle_CureStatus(battler_index, 0x38);
        acc = &g_Battle.pending_status;
        *acc |= STATUS_PARALYZED;
        func_801DDFEC(battler_index);
        func_801DD14C(battler_index);
    }
    if ((status_mask & STATUS_UNK_11) && !(status & STATUS_UNK_11)) {
        Battle_CureStatus(battler_index, 0x7E);
        acc = &g_Battle.pending_status;
        *acc |= STATUS_UNK_11;
        func_801DDFEC(battler_index);
        func_801DD14C(battler_index);
    }
    slot = battler_index;
    if (BATTLER_IS_PLAYER(slot)) {
        GFX_FreePaletteFadeTarget(&g_Game.members[slot].header.flags);
        merged                          = g_Game.members[slot].chr.status;
        merged                          = merged | g_Battle.pending_status;
        g_Game.members[slot].chr.status = merged;
    } else {
        GFX_FreePaletteFadeTarget(&((volatile EnemyBattler*)g_BattleEnemies)[slot].header);
        merged                       = ENEMY_COMBATANT(slot).status | g_Battle.pending_status;
        ENEMY_COMBATANT(slot).status = merged;
    }
    func_801DDAB4(merged);
}

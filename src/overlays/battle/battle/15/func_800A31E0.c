#include "battle_15.h"

/* Applies the status bits named by input_mask to one battler (players below 3,
 * enemies from 3): each bit is set in g_Battle.pending_status unless the battler already has
 * it or a blocking status, then the merged word is stored back and published. */
MATCH void func_800A31E0(u8 selection_kind, u16 input_mask) {
    u16  status;
    u8   slot;
    u32  merged;
    u16* acc;

    if (selection_kind < 3) {
        status = g_Game.members[selection_kind].chr.status;
    } else {
        status = ENEMY_COMBATANT(selection_kind).status;
    }
    if ((input_mask & STATUS_POISONED) && !(status & STATUS_POISONED)) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_POISONED;
    }
    if ((input_mask & STATUS_UNK_0) && !(status & STATUS_UNK_0)) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_UNK_0;
    }
    if ((input_mask & STATUS_UNK_1) && !(status & STATUS_UNK_1)) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_UNK_1;
    }
    if (input_mask & STATUS_SLEEPING) {
        if (func_800A3638(selection_kind, 6) & BYTE_MASK) {
            if (!(status & (STATUS_UNK_11 | STATUS_SLEEPING))) {
                func_800A36F0(selection_kind, 0x38);
                acc = &g_Battle.pending_status;
                *acc |= STATUS_SLEEPING;
                func_801DDFEC(selection_kind);
                func_801DD14C(selection_kind);
            }
        }
    }
    if ((input_mask & STATUS_CONFUSED) && (func_800A3638(selection_kind, 8) & BYTE_MASK) && !(status & (STATUS_UNK_11 | STATUS_SLEEPING | STATUS_CONFUSED | STATUS_PARALYZED))) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_CONFUSED;
        func_801DDFEC(selection_kind);
        g_BattleEffects[selection_kind].arg.sway = 0;
        if (selection_kind < 3) {
            g_Game.members[selection_kind].u.turn.command.type = 0;
            g_Game.members[selection_kind].u.turn.damage_flags.volatile_value &= ~2;
            g_Game.members[selection_kind].u.turn.action_flags.volatile_value &= ~4;
        } else {
            ENEMY_COMBATANT(selection_kind).turn.command.type = 0;
            ENEMY_COMBATANT(selection_kind).turn.damage_flags.value &= ~2;
        }
    }
    if ((input_mask & STATUS_BLIND) && (func_800A3638(selection_kind, 9) & BYTE_MASK) && (func_800A36BC(selection_kind, 0x2B) & BYTE_MASK) &&
        !(status & (STATUS_UNK_11 | STATUS_BLIND | STATUS_PARALYZED))) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_BLIND;
    }
    if ((input_mask & STATUS_SILENCED) && !(status & (STATUS_UNK_11 | STATUS_SILENCED | STATUS_PARALYZED))) {
        acc = &g_Battle.pending_status;
        *acc |= STATUS_SILENCED;
    }
    if ((input_mask & STATUS_PARALYZED) && !(status & (STATUS_UNK_11 | STATUS_PARALYZED))) {
        func_800A36F0(selection_kind, 0x38);
        acc = &g_Battle.pending_status;
        *acc |= STATUS_PARALYZED;
        func_801DDFEC(selection_kind);
        func_801DD14C(selection_kind);
    }
    if ((input_mask & STATUS_UNK_11) && !(status & STATUS_UNK_11)) {
        func_800A36F0(selection_kind, 0x7E);
        acc = &g_Battle.pending_status;
        *acc |= STATUS_UNK_11;
        func_801DDFEC(selection_kind);
        func_801DD14C(selection_kind);
    }
    slot = selection_kind;
    if (BATTLER_IS_PLAYER(slot)) {
        GFX_FreePaletteFadeTarget(&g_Game.members[slot].header.flags);
        merged                          = g_Game.members[slot].chr.status;
        merged                          = merged | g_Battle.pending_status;
        g_Game.members[slot].chr.status = merged;
    } else {
        GFX_FreePaletteFadeTarget(((volatile BattleEnemy*)g_BattleEnemies)[slot].unk_00);
        merged                       = ENEMY_COMBATANT(slot).status | g_Battle.pending_status;
        ENEMY_COMBATANT(slot).status = merged;
    }
    func_801DDAB4(merged);
}

#include "battle_15.h"

/* Applies the status bits named by input_mask to one battler (players below 3,
 * enemies from 3): each bit is set in g_BattlePendingStatus unless the battler already has
 * it or a blocking status, then the merged word is stored back and published. */
MATCH void func_800A31E0(u8 selection_kind, u16 input_mask) {
    u16  status;
    u32  row;
    u8   slot;
    u32  merged;
    u16* acc;

    if (selection_kind < 3) {
        status = g_BattlePartyBattlers[selection_kind].chr.status;
    } else {
        status = ENEMY_COMBATANT(selection_kind).status;
    }
    if ((input_mask & 0x80) && !(status & STATUS_POISONED)) {
        acc = &g_BattlePendingStatus;
        *acc |= 0x80;
    }
    if ((input_mask & 1) && !(status & 1)) {
        acc = &g_BattlePendingStatus;
        *acc |= 1;
    }
    if ((input_mask & 2) && !(status & 2)) {
        acc = &g_BattlePendingStatus;
        *acc |= 2;
    }
    if (input_mask & STATUS_SLEEPING) {
        if (func_800A3638(selection_kind, 6) & BYTE_MASK) {
            if (!(status & (0x800 | STATUS_SLEEPING))) {
                func_800A36F0(selection_kind, 0x38);
                acc = &g_BattlePendingStatus;
                *acc |= STATUS_SLEEPING;
                func_801DDFEC(selection_kind);
                func_801DD14C(selection_kind);
            }
        }
    }
    if ((input_mask & STATUS_CONFUSED) && (func_800A3638(selection_kind, 8) & BYTE_MASK) &&
        !(status & (0x800 | STATUS_SLEEPING | STATUS_CONFUSED | STATUS_PARALYZED))) {
        acc = &g_BattlePendingStatus;
        *acc |= STATUS_CONFUSED;
        func_801DDFEC(selection_kind);
        D_801EC339[selection_kind * 0x78] = 0;
        if (selection_kind < 3) {
            g_BattlePartyBattlers[selection_kind].turn.command.type = 0;
            g_BattlePartyBattlers[selection_kind].turn.damage_flags.volatile_value &= ~2;
            g_BattlePartyBattlers[selection_kind].turn.action_flags.volatile_value &= ~4;
        } else {
            row                         = selection_kind - 3;
            D_801EB721[row * 0x118 + 4] = 0;
            D_801EB730[row].flags &= ~2;
        }
    }
    if ((input_mask & STATUS_BLIND) && (func_800A3638(selection_kind, 9) & BYTE_MASK) &&
        (func_800A36BC(selection_kind, 0x2B) & BYTE_MASK) && !(status & (0x800 | STATUS_BLIND | STATUS_PARALYZED))) {
        acc = &g_BattlePendingStatus;
        *acc |= STATUS_BLIND;
    }
    if ((input_mask & STATUS_SILENCED) && !(status & (0x800 | STATUS_SILENCED | STATUS_PARALYZED))) {
        acc = &g_BattlePendingStatus;
        *acc |= STATUS_SILENCED;
    }
    if ((input_mask & STATUS_PARALYZED) && !(status & (0x800 | STATUS_PARALYZED))) {
        func_800A36F0(selection_kind, 0x38);
        acc = &g_BattlePendingStatus;
        *acc |= STATUS_PARALYZED;
        func_801DDFEC(selection_kind);
        func_801DD14C(selection_kind);
    }
    if ((input_mask & 0x800) && !(status & 0x800)) {
        func_800A36F0(selection_kind, 0x7E);
        acc = &g_BattlePendingStatus;
        *acc |= 0x800;
        func_801DDFEC(selection_kind);
        func_801DD14C(selection_kind);
    }
    slot = selection_kind;
    if (BATTLER_IS_PLAYER(slot)) {
        GFX_FreePaletteFadeTarget(&g_BattlePartyBattlers[slot].header.flags);
        merged                                 = g_BattlePartyBattlers[slot].chr.status;
        merged                                 = merged | g_BattlePendingStatus;
        g_BattlePartyBattlers[slot].chr.status = merged;
    } else {
        GFX_FreePaletteFadeTarget(((volatile BattleEnemyRecord*)g_BattleEnemies)[slot].unk_00);
        merged                       = ENEMY_COMBATANT(slot).status | g_BattlePendingStatus;
        ENEMY_COMBATANT(slot).status = merged;
    }
    func_801DDAB4(merged);
}

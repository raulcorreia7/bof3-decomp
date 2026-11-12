#include "battle_03.h"

/* picks the auto-target result byte for one enemy slot: dispatches on the global battle mode byte (1 =
 * enemy-state helper, 4 = decide from enemy targeting flags, otherwise read the preset table entry directly).
 */
#ifdef NON_MATCHING
NON_MATCHING u8 Battle_PickEnemyTarget(u8 enemy_index) {
    u16 flags;
    u8  targeting_flags;
    u8  index;
    u8  picked;

    index = enemy_index;
    switch (g_Battle.action_type) {
        case 1:
            flags = g_BattleEnemyBattlers[index].event_flags;
            if (flags & 1) {
                picked = func_801E30B8(index);
                if (picked == GAME_NONE) {
                    return Battle_PickFormationTarget();
                }
                return picked;
            }
            if (flags & 0x10) {
                return func_801E2D90(index);
            }
            return Battle_PickFormationTarget();
        case 4:
            targeting_flags = D_801CA718[g_BattleEnemyBattlers[index].turn.command.id][0];
            flags           = g_BattleEnemyBattlers[index].event_flags;
            if (flags & 1) {
                if (targeting_flags & ABILITY_TARGET_ALL) {
                    if (targeting_flags & ABILITY_TARGET_BOTH_SIDES) {
                        if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                            return 0xC0;
                        }
                    }
                    if (targeting_flags & ABILITY_TARGET_OPPONENT) {
                        return 0x40;
                    }
                    return 0x80;
                }
                if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                    return index + 3;
                }
                if (targeting_flags & ABILITY_TARGET_OPPONENT) {
                    return func_801E2D4C(index);
                }
                if (flags & 0x10) {
                    return func_801E2D90(index);
                }
                return Battle_PickFormationTarget();
            }
            if (targeting_flags & ABILITY_TARGET_ALL) {
                if (targeting_flags & ABILITY_TARGET_BOTH_SIDES) {
                    if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                        return 0xC0;
                    }
                }
                if (targeting_flags & ABILITY_TARGET_OPPONENT) {
                    return 0x80;
                }
                return 0x40;
            }
            if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                return index + 3;
            }
            if (!(targeting_flags & ABILITY_TARGET_OPPONENT)) {
                return Battle_PickLowestHpTarget();
            }
            if (flags & 0x10) {
                return func_801E2D90(index);
            }
            return Battle_PickFormationTarget();
        default:
            return g_BattleEnemyBattlers[enemy_index].slot;
    }
}
#else
INCLUDE_ASM(Battle_PickEnemyTarget);
#endif

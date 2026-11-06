#include "battle_03.h"

/* func_801D3844 */
MATCH u8 Battle_PickTarget(void) {
    u16* state;
    u8   kind;
    u8   targeting_flags;
    u16  selected_kind;

    state = (u16*)&g_BattleActionId;

    if (*state == 36) {
        kind = g_BattleRecallAbilities[RANDOM_MASK(0x1Fu)];
    } else {
        kind = 0u;
    }

    if ((*state == 37) || (*state == 140)) {
        kind = g_BattleMagicShuffleAbilities[RANDOM_MASK(0x1Fu)];
    }

    targeting_flags                                  = g_Abilities[kind].targeting_flags;
    selected_kind                                    = kind;
    g_BattleActionId                                 = selected_kind;
    *(u16*)(((*(volatile u8**)&g_BattleAction) + 2)) = selected_kind;

    if (targeting_flags & ABILITY_TARGET_ALL) {
        if (targeting_flags & ABILITY_TARGET_BOTH_SIDES) {
            if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
                return 0xC0u;
            }
        }

        if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
            if (targeting_flags & ABILITY_TARGET_OPPONENT) {
                return 0x40u;
            }
            return 0x80u;
        }

        if (targeting_flags & ABILITY_TARGET_OPPONENT) {
            return 0x80u;
        }
        return 0x40u;
    }

    if (!(targeting_flags & ABILITY_TARGET_SELECT)) {
        return g_BattleActiveBattler;
    }

    if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        if (targeting_flags & ABILITY_TARGET_OPPONENT) {
            return func_800A955C();
        }
    } else if (!(targeting_flags & ABILITY_TARGET_OPPONENT)) {
        return func_800A955C();
    }

    return func_800A94A8();
}

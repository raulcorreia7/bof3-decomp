#include "battle_03.h"

/* The battler counts the two weight tables are sized for. */
#define BATTLE_TWO_TARGET_COUNT   2
#define BATTLE_THREE_TARGET_COUNT 3

/* Picks a random live target slot weighted by the formation table. */
/* func_801E2E30 */
MATCH u8 Battle_PickFormationTarget(void) {
    u8 total   = 0;
    u8 running = 0;
    u8 index;
    u8 pick;

    switch (g_Battle.party_count) {
        default:
            return 0;
        case 1:
            return 0;
        case BATTLE_TWO_TARGET_COUNT:
            for (index = 0; index < BATTLE_TWO_TARGET_COUNT; index++) {
                if (!Battle_SlotIsBlocked(index)) {
                    total += s_BattlePartialPartyTargetWeights[g_PartyFormation][index];
                }
            }
            pick = RANDOM_MOD(total);
            for (index = 0; index < BATTLE_TWO_TARGET_COUNT; index++) {
                if (Battle_SlotIsBlocked(index)) {
                    continue;
                }
                running += s_BattlePartialPartyTargetWeights[g_PartyFormation][index];
                if (pick < running) {
                    return index;
                }
            }
            return index;
        case BATTLE_THREE_TARGET_COUNT:
            for (index = 0; index < BATTLE_THREE_TARGET_COUNT; index++) {
                if (!Battle_SlotIsBlocked(index)) {
                    total += s_BattleFullPartyTargetWeights[g_PartyFormation][index];
                }
            }
            pick = RANDOM_MOD(total);
            for (index = 0; index < BATTLE_THREE_TARGET_COUNT; index++) {
                if (Battle_SlotIsBlocked(index)) {
                    continue;
                }
                running += s_BattleFullPartyTargetWeights[g_PartyFormation][index];
                if (pick < running) {
                    return index;
                }
            }
            return index;
    }
}

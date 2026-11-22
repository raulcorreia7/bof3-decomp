#include "battle_15.h"

MATCH s32 Battle_AppendComboIds(u8 combination, u8 count) {
    Character* character;
    u8         limit;
    u8         i;

    character = &g_Game.members[g_Battle.active_battler].chr;
    limit     = count;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        u8 j;

        if (D_800B4EB0[combination][i] == 0) {
            return limit;
        }
        for (j = 0; j < limit; j++) {
            if (character->abilities.attack[j] == D_800B4EB0[combination][i]) {
                /* id already listed */
                goto next;
            }
        }
        if (limit == 9) {
            return limit;
        }
        character->abilities.attack[limit] = D_800B4EB0[combination][i];
        limit++;
    next:;
    }
    return limit;
}

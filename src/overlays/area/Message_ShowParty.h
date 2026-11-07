#include "common/util.h"
/* Show a party member's message: the first slot whose tag equals the first byte
 * of a battle record row, then game state 2. One source for the world area
 * overlays; each member names its record slot and declares the loop counters.
 * Every change here must verify every member address. Kept: the slot literal
 * folds into the g_PartyMemberMessages address; as an inline it stays in a
 * register (tested), and the body returns from the member. */
#define WORLD_SHOW_PARTY_MESSAGE(slot, i, j)                                                          \
    for (i = 0; i < PARTY_MEMBER_MESSAGE_COUNT; i++) {                                                \
        for (j = 0; j < g_PartySize; j++) {                                                           \
            if (g_BattlePartyBattlers[j].chr.character_id == g_PartyMemberMessages[(slot)].tags[i]) { \
                Message_StartAreaMessage(g_PartyMemberMessages[(slot)].messages[i]);                  \
                g_GameStateIndex = GAME_REQUEST_MESSAGE;                                              \
                return;                                                                               \
            }                                                                                         \
        }                                                                                             \
    }

#include "common/util.h"
/* Show a party member's message. */
#define WORLD_SHOW_PARTY_MESSAGE(slot, i, j)                                                   \
    for (i = 0; i < PARTY_MEMBER_MESSAGE_COUNT; i++) {                                         \
        for (j = 0; j < g_Game.party_size; j++) {                                              \
            if (g_Game.members[j].chr.character_id == g_PartyMemberMessages[(slot)].tags[i]) { \
                Message_StartAreaMessage(g_PartyMemberMessages[(slot)].messages[i]);           \
                g_GameStateIndex = GAME_REQUEST_MESSAGE;                                       \
                return;                                                                        \
            }                                                                                  \
        }                                                                                      \
    }

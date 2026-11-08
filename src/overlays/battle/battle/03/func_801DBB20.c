#include "battle_03.h"

MATCH PartyMember* func_801DBB20(u8 selector) {
    u8 i;

    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (g_Game.members[i].chr.character_id == selector) {
            return &g_Game.members[i];
        }
    }

    return NULL;
}

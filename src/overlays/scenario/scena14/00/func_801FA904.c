#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH u16 func_801FA904(u8* tags, u16* messages) {
    u8 i;
    u8 j;

    for (i = 0; i < PARTY_MEMBER_MESSAGE_COUNT; i++) {
        for (j = 0; j < g_PartySize; j++) {
            if (g_Game.members[j].chr.character_id == tags[i]) {
                UI_MessageStartArea((s16)messages[i]);
                do {
                    g_GameStateIndex = GAME_REQUEST_MESSAGE;
                } while (0); /* FAKE: keeps the state store before the return value's reload. */
                return messages[i];
            }
        }
    }
    return MESSAGE_NONE;
}

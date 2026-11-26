#include "engine/game/00/game_00.h"

/* func_801BEDD0 */
MATCH void Game_BattleQueueEncounterTurns(void) {
    s32 index;
    u8* work;
    s32 count;

    index = 0;
    count = g_PartySize;
    if (count <= index) {
        return;
    }
    work = (u8*)g_Game.members + index * BATTLE_PARTY_STRIDE;
    do {
        SELF_SET(work);
        SELF(Actor)->param.unk_0B = Actor_GetTurnStep(s_RouteIndexByMode[g_Battle.scroll_dir]);
        work += BATTLE_PARTY_STRIDE;
        index += 1;
    } while (index < g_Game.party_size);
}

#include "engine/game/00/game_00.h"

/* func_801BFAC4 */
MATCH void Game_BattleRunPartyAnims(void) {
    u8* work;
    s32 i;

    i = 0;
    while (i < g_PartySize) {
        work        = (u8*)g_Game.members + i * BATTLE_PARTY_STRIDE;
        g_GameState = work;
        SELF_SET(work);
        Script_AnimStepLoop();
        i++;
    }
}

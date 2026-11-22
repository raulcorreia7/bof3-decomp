#include "engine/game/00/game_00.h"

/* func_80197E54 */
MATCH void Game_BattleBeginEntrance(void) {
    u8   local_ready;
    u16* state;

    local_ready = Game_BattleIsPartyInPlace();
    Actor_RunInteractions();
    Area_RunLoadingFrame();
    if (EMI_IsReady() && local_ready) {
        g_AreaCameraSpeed            = 0;
        g_Battle.outcome.event_flags = 0;
        g_Battle.phase.mode          = BATTLE_MODE_ENTRANCE;
        g_Battle.phase.step          = 0;
        g_Battle.phase.sub_step      = 0;
        g_Battle.ui_step             = 0;
        g_Battle.ui_mode             = 0;
        g_Battle.party_count         = Party_CountOrder(PARTY_ORDER_BATTLE);
        state                        = &g_GameEntrySubstate;
        (*state)++;
    }
}

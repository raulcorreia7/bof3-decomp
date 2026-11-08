#include "game_00.h"

MATCH void func_80197E54(void) {
    u8   local_ready;
    u16* state;

    local_ready = func_801BF78C();
    func_801A06D8();
    func_801992B8();
    if (EMI_LoaderIsReady() && local_ready) {
        g_AreaCameraStep            = 0;
        g_BattleOutcome.event_flags = 0;
        g_BattleMode                = 0;
        g_BattleStep                = 0;
        g_BattleSubStep             = 0;
        g_BattleUIStep              = 0;
        g_BattleUIState             = 0;
        g_BattlePartyCount          = Party_CountOrder(PARTY_ORDER_BATTLE);
        state                       = &g_GameEntrySubstate;
        (*state)++;
    }
}

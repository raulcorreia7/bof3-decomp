#include "game_00.h"

MATCH void func_80197E54(void) {
    u8   local_ready;
    u16* state;

    local_ready = func_801BF78C();
    func_801A06D8();
    func_801992B8();
    if (EMI_LoaderIsReady() && local_ready) {
        g_AreaCameraStep             = 0;
        g_Battle.outcome.event_flags = 0;
        g_Battle.phase.mode          = 0;
        g_Battle.phase.step          = 0;
        g_Battle.phase.sub_step      = 0;
        g_Battle.ui_step             = 0;
        g_Battle.ui_state            = 0;
        g_Battle.party_count         = Party_CountOrder(PARTY_ORDER_BATTLE);
        state                        = &g_GameEntrySubstate;
        (*state)++;
    }
}

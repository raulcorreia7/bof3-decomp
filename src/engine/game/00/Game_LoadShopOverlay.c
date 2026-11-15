#include "game_00.h"

MATCH void Game_LoadShopOverlay(void) {
    Actor* work;

    if (D_8014865C >= 0) {
        work = &g_Actors[D_8014865C];
        TASK_SET(work);
        if (work->unk_18 == 9) {
            g_GameEntryState    = GAME_STATE_FIELD;
            g_GameEntrySubstate = 0u;
            g_GameStateIndex    = GAME_REQUEST_IDLE;
            if (!(work->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                work->direction_08 = work->unk_79;
                func_8015BAC4(g_Task->direction_08);
                work->interaction_flags = (work->interaction_flags | ACTOR_FLAG_MOVING);
            }
            work->interaction_flags = (work->interaction_flags & ~ACTOR_FLAG_SCRIPT_PENDING);
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            Area_RunFrame();
            return;
        }
    }
    EMI_LoadArchive(EMI_SLOT_SHOP);
    while (EMI_IsReady() == 0) {
        func_801992B8();
        SYS_ThreadWait(1u);
    }
    GFX_CopyPalette(1u);
    GFX_CopyPalette(2u);
    g_GfxPalettePending = 1u;
    Area_RunFrame();
    VOL(u16, g_GameEntrySubstate) += 1u;
}

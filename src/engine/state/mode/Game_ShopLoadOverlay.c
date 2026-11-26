#include "engine/game/00/game_00.h"

MATCH void Game_ShopLoadOverlay(void) {
    Actor* work;

    if (D_8014865C >= 0) {
        work = &g_Actors[D_8014865C];
        SELF_SET(work);
        if (work->unk_18 == 9) {
            g_GameEntryState    = GAME_MODE_FIELD;
            g_GameEntrySubstate = 0u;
            g_GameStateIndex    = GAME_REQUEST_IDLE;
            if (!(work->option_flags & ACTOR_OPT_ROUTE_LOCKED)) {
                work->direction = work->unk_79;
                Script_DispatchSelector(SELF(Actor)->direction);
                work->interaction_flags = (work->interaction_flags | ACTOR_INTERACTION_MOVING);
            }
            work->interaction_flags = (work->interaction_flags & ~ACTOR_INTERACTION_SCRIPT_PENDING);
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            Area_RunFrame();
            return;
        }
    }
    EMI_ArchiveLoad(EMI_SLOT_SHOP);
    while (EMI_IsReady() == 0) {
        Area_RunLoadingFrame();
        SYS_ThreadWait(1u);
    }
    GFX_PaletteCopy(1u);
    GFX_PaletteCopy(2u);
    g_GfxPalettePending = 1u;
    Area_RunFrame();
    FAKE_VOLATILE(u16, g_GameEntrySubstate) += 1u;
}

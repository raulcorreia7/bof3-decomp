#include "game_00.h"

MATCH void Game_LoadShopOverlay(void) {
    Actor* work;

    if (D_8014865C >= 0) {
        work                 = &g_Actors[D_8014865C];
        SP_REF(Actor*, 0x44) = work;
        if (work->unk_18 == 9) {
            g_GameEntryState    = 2u;
            g_GameEntrySubstate = 0u;
            g_GameStateIndex    = GAME_REQUEST_IDLE;
            if (!(work->unk_07 & ACTOR_OPT_ROUTE_LOCKED)) {
                work->direction_08 = work->unk_79;
                func_8015BAC4(g_SpadWork->direction_08);
                work->flags_74 = (u8)(work->flags_74 | ACTOR_FLAG_MOVING);
            }
            work->flags_74 = (u8)(work->flags_74 & ~ACTOR_FLAG_SCRIPT_PENDING);
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            Area_RunFrame();
            return;
        }
    }
    EMI_LoaderStreamInitSlot(EMI_SLOT_SHOP);
    while (EMI_LoaderIsReady() == 0) {
        func_801992B8();
        CallbackWait(1u);
    }
    GFX_CopyPalette(1u);
    GFX_CopyPalette(2u);
    g_GfxPalettePending = 1u;
    Area_RunFrame();
    VOL(u16, g_GameEntrySubstate) += 1u;
}

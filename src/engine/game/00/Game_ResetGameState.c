#include "game_00.h"

MATCH void Game_ResetGameState(void) {
    u16 selection_seed;
    u16 world_flags;
    u32 context_a;
    u32 context_b;
    u8  context_kind;

    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    g_AreaDrawMode  = 6u;
    Party_BuildBattlers(0u);
    selection_seed = D_801448FC;
    g_GameAreaId   = 0xFFFFu;
    world_flags    = g_AreaWalkFlags;
    /* FAKE: retail keeps the flags load ahead of the context loads. */
    MATCH_FAKE_BARRIER();
    context_a         = D_80144900;
    context_b         = D_80144904;
    context_kind      = D_801448FF;
    D_80146256        = 0u;
    D_80143F49        = 0u;
    D_80143F4A        = 0u;
    D_80143F4B        = 0u;
    g_BattleOptions   = 0u;
    g_BattleEncounter = 0u;
    D_80146880        = 0u;
    D_80146881        = 0u;
    g_AreaWalkFlags   = world_flags | (0x4000u | AREA_WALK_ENTRY_PENDING);
    Game_RequestAreaChange(selection_seed, context_a, context_b, context_kind);

    if (*(u32*)&g_PlayClock != 0u) {
        g_GamePrevSelection = g_SndBgmId;
    }

    g_SndBgmId       = 0xFFu;
    g_GameEntryState = 1u;
}

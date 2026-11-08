#include "game_00.h"

MATCH void Game_NewGame(void) {
    u16 area_id;
    u16 world_flags;
    u32 entry_x;
    u32 entry_y;
    u8  entry_facing;

    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    g_AreaDrawMode  = 6u;
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    area_id      = g_SaveAreaId;
    g_GameAreaId = 0xFFFFu;
    world_flags  = g_AreaWalkFlags;
    /* FAKE: retail keeps the flags load ahead of the context loads. */
    FAKE_BARRIER();
    entry_x                  = g_SaveEntryX;
    entry_y                  = g_SaveEntryY;
    entry_facing             = g_SaveEntryFacing;
    D_80146256               = 0u;
    D_80143F49               = 0u;
    D_80143F4A               = 0u;
    D_80143F4B               = 0u;
    g_Battle.outcome.options = 0u;
    g_Battle.encounter       = 0u;
    D_80146880               = 0u;
    D_80146881               = 0u;
    g_Game.walk_flags        = world_flags | (0x4000u | AREA_WALK_ENTRY_PENDING);
    Game_RequestAreaChange(area_id, entry_x, entry_y, entry_facing);

    if (*(u32*)&g_PlayClock != 0u) {
        g_GamePrevSelection = g_SndBGMId;
    }

    g_SndBGMId       = 0xFFu;
    g_GameEntryState = 1u;
}

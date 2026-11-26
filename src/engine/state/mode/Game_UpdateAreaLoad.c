#include "engine/game/00/game_00.h"

MATCH void Game_UpdateAreaLoad(void) {
    u16 area_id;
    u32 entry_x;
    u32 entry_y;
    u8  entry_facing;
    u16 world_flags;
    u16 final_world_flags;
    u8  ui_mode;
    s32 pending_world;

    area_id           = g_GameEntryAreaId;
    entry_x           = g_GameEntryPosX;
    world_flags       = g_AreaWalkFlags;
    entry_y           = g_GameEntryPosY;
    entry_facing      = g_GameEntryFacing;
    g_Game.walk_flags = world_flags & ~AREA_WALK_ENTRY_ACTIVE;
    Game_EnterArea(area_id, entry_x, entry_y, entry_facing);

    if (g_GameRequestFlags & AREA_LOAD_FLAG_FISHING) {
        g_GameEntryState = GAME_MODE_FISHING;
        return;
    }

    ui_mode = g_GameRequestType;
    if ((u8)(ui_mode + 2u) >= 2u) {
        UI_ModeSet(ui_mode);
        Area_WaitWindowEffect(1u);
        if (LOBU(g_GameRequestFlags) & 0x1u) {
            Area_RequestLinkAtCell(g_AreaCamera.scroll_x.part.integer, g_AreaCamera.scroll_y.part.integer);
        }
    } else if (ui_mode == 0xFEu) {
        g_AreaDrawFlags = 0u;
    }

    if (LOBU(g_GameRequestFlags) & 0x1u) {
        g_GameEntryMode = 10u;
    } else if (LOHU(g_GameAreaId) == AREA_ID_DESERT_OF_DEATH_MAP) {
        g_GameEntryMode = 20u;
    } else {
        g_GameEntryMode = 0u;
    }

    pending_world = LOHU(g_GameAreaId);
    if (pending_world != AREA_ID_DESERT_OF_DEATH_MAP) {
        Area_EncounterRollThreshold(1u);
    }

    final_world_flags = g_AreaWalkFlags;
    g_GameStateIndex  = GAME_REQUEST_IDLE;
    g_GameEntryState  = GAME_MODE_FIELD;
    g_Game.walk_flags = final_world_flags & ~AREA_WALK_ENTRY_PENDING;
}

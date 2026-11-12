#include "game_00.h"

MATCH void Game_UpdateAreaLoad(void) {
    u16 context_seed;
    u32 context_a;
    u32 context_b;
    u8  context_kind;
    u16 world_flags;
    u16 final_world_flags;
    u8  request_kind;
    s32 pending_world;

    context_seed      = g_GameContextSeed;
    context_a         = g_GameEntryPosX;
    world_flags       = g_AreaWalkFlags;
    context_b         = g_GameEntryPosY;
    context_kind      = g_GameContextKind;
    g_Game.walk_flags = world_flags & ~AREA_WALK_ENTRY_ACTIVE;
    func_8019FAA0(context_seed, context_a, context_b, context_kind);

    if (g_GameRequestFlags & 0x8u) {
        g_GameEntryState = GAME_STATE_FISHING;
        return;
    }

    request_kind = g_GameRequestKind;
    if ((u8)(request_kind + 2u) >= 2u) {
        UI_SetMode(request_kind);
        func_80198BC4(1u);
        if (LOBU(g_GameRequestFlags) & 0x1u) {
            func_801A0048(g_AreaTargetCellX, g_AreaTargetCellY);
        }
    } else if (request_kind == 0xFEu) {
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
        Area_RollEncounterThreshold(1u);
    }

    final_world_flags = g_AreaWalkFlags;
    g_GameStateIndex  = GAME_REQUEST_IDLE;
    g_GameEntryState  = GAME_STATE_FIELD;
    g_Game.walk_flags = final_world_flags & ~AREA_WALK_ENTRY_PENDING;
}

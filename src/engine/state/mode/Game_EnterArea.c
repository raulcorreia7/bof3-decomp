#include "engine/game/00/game_00.h"
#include "common/copy.h"

/* Enters an area: keeps the last position, starts its music, loads it when it changed, then sets up the view, party and entry walk. */
/* func_8019FAA0 */
MATCH void Game_EnterArea(u16 area_id, u32 entry_x, u32 entry_y, u8 entry_facing) {
    AreaLoad* entry;
    u16       world_flags;
    u8        seed;
    u8        counter;
    u8        size;

    if ((entry_facing & 0x80u) != 0)
        g_AreaWalkFlags |= AREA_WALK_MAP_LOADING;
    else
        g_AreaWalkFlags &= 0x7FFFu;
    Actor_ClearAll();
    GFX_PaletteResetFades();

    g_GameLastAreaId   = g_GameAreaId;
    g_GameLastCellType = g_GameCellType;
    g_GameLastX        = g_AreaScrollTargetX;
    g_GameLastY        = g_AreaScrollTargetY;
    seed               = g_GamePrevSelection;
    if (seed != 0xFFu)
        SND_BGMStart(seed, 100, 8);
    else
        g_SndBGMId = 0xFFu;

    if (g_GameAreaId != area_id && g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_GameAreaId = area_id;
        EMI_ArchiveLoad((u32)(area_id + EMI_SLOT_AREA));
        while (EMI_IsReady() == 0)
            SYS_ThreadWait(1u);
        entry              = (AreaLoad*)g_AreaLoads[g_GameAreaId];
        g_GameRequestFlags = entry->flags;
        GFX_PaletteReset();
        g_GfxPalettePending = 1u;
    }

    func_801BFF9C(entry_x, entry_y, (u32)entry_facing);
    g_GameCellType = func_801A0348(g_AreaTargetCellX, g_AreaTargetCellY);
    Area_InitMapRenderer();

    entry = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    if (entry->matrix != 0) {
        SetColorMatrix((MATRIX*)entry->matrix);
        entry                = (AreaLoad*)g_AreaLoads[g_GameAreaId];
        *(Cpy8u*)&D_801481E0 = *(Cpy8u*)((u8*)entry->matrix + 0x20);
    } else {
        SetColorMatrix((MATRIX*)D_8018214C);
        *(Cpy8u*)&D_801481E0 = *(Cpy8u*)s_ScriptCopyBlock;
    }

    if (((s8)g_ScenarioState.flags_01 & SCENARIO_STATE_CHAPTER_ADVANCE) != 0) {
        counter                     = g_ScenarioState.scenario_id;
        g_ScenarioState.scenario_id = (u8)(counter + 1);
        if ((s8)(counter + 1) == 16)
            g_ScenarioState.scenario_id = (u8)(counter + 2);
        Scene_Start(g_ScenarioState.scenario_id);
    }

    entry = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    Area_RunSetupStream(entry->handler);
    entry = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    if (entry->callback != 0)
        entry->callback();

    SYS_ClearFlag(g_SceneEventFlags, 0x1Cu);
    g_ScenarioState.mode_02 = 1u;
    Game_ScenarioUpdate();
    func_801C05AC();

    world_flags = g_AreaWalkFlags;
    if (!(world_flags & AREA_WALK_MAP_LOADING)) {
        if (!(g_GameFlags & 0x800u)) {
            if (world_flags & 0x80u) {
                func_8019FF88(1, entry_x, entry_y);
            } else if (world_flags & 0x100u) {
                func_8019FF88(2, entry_x, entry_y);
            } else if (world_flags & 0x200u) {
                func_8019FF88(3, entry_x, entry_y);
            } else {
                if (g_PartySize < 2u)
                    goto end;
                func_8019FF88(0, entry_x, entry_y);
                if (!(g_GameFlags & 0x800u) && !(g_AreaWalkFlags & AREA_WALK_MAP_LOADING))
                    Area_CellSetPalette(g_AreaTargetCellX, g_AreaTargetCellY);
            }
            size = g_PartySize;
            if (size >= 2u) {
                world_flags     = g_AreaWalkFlags;
                g_AreaWalkFlags = world_flags | 0x12u;
                if (size == 3u)
                    g_AreaWalkFlags = world_flags | 0x16u;
            }
        }
    } else if (entry_facing & 0x80u) {
        g_Game.unk_3CE[2] = 0u;
        Scene_SetupParty((u32)(entry_facing & 0x7Fu));
        g_AreaWalkFlags &= ~AREA_WALK_ACCEPT_LOCK;
        Party_RunFrame();
    }
end:
    g_AreaWalkFlags &= 0xEE7Fu;
}

#include "game_00.h"

typedef struct GameCopyBlock {
    u8 data[8];
} GameCopyBlock;

#ifdef NON_MATCHING
NON_MATCHING void func_8019FAA0(u16 area_id, u32 entry_x, u32 entry_y, u8 entry_facing) {
    AreaLoad* entry;
    void*     matrix;
    u32       word_a;
    u32       word_b;
    u16       world;
    u16       world_flags;
    u8        flag;
    u8        seed;
    u8        counter;
    u8        mode;

    if ((entry_facing & 0x80u) != 0)
        g_Game.walk_flags |= AREA_WALK_MAP_LOADING;
    else
        g_Game.walk_flags &= 0x7FFFu;
    Actor_ClearAll();
    GFX_ResetPaletteFades();

    word_a     = (u32)g_AreaScrollTargetX;
    world      = g_GameAreaId;
    flag       = D_80143F03;
    word_b     = (u32)g_AreaScrollTargetY;
    D_80143F08 = word_a;
    seed       = g_GamePrevSelection;
    D_80143F04 = world;
    D_80143F06 = flag;
    D_80143F0C = word_b;
    if (seed == 0xFFu)
        g_SndBGMId = 0xFFu;
    else
        SND_StartBGM(seed, 100, 8);

    if (g_GameAreaId != area_id) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            g_GameAreaId = area_id;
            EMI_LoadArchive((u32)(area_id + EMI_SLOT_AREA));
            while (EMI_IsReady() == 0)
                SYS_ThreadWait(1u);
        }
    }

    entry              = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    g_GameRequestFlags = entry->flag_32;
    GFX_ResetPalette();
    g_GfxPalettePending = 1u;

    func_801BFF9C(entry_x, entry_y, (u32)entry_facing);
    D_80143F03 = func_801A0348(g_AreaTargetCellX, g_AreaTargetCellY);
    func_80153DE8();

    entry  = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    matrix = entry->matrix;
    if (matrix != 0) {
        SetColorMatrix((MATRIX*)matrix);
        entry                       = (AreaLoad*)g_AreaLoads[g_GameAreaId];
        *(GameCopyBlock*)D_801581E0 = *(GameCopyBlock*)((u8*)entry->matrix + 0x20);
    } else {
        SetColorMatrix((MATRIX*)D_8018214C);
        *(GameCopyBlock*)D_801581E0 = *(GameCopyBlock*)s_ScriptCopyBlock;
    }

    if ((g_SceneState.flags_01 & SCENE_STATE_CHAPTER_ADVANCE) != 0) {
        counter                  = g_SceneState.scenario_id;
        g_SceneState.scenario_id = (u8)(counter + 1);
        if ((s8)(counter + 1) == 16) {
            g_SceneState.scenario_id = (u8)(counter + 2);
            Scene_Start(g_SceneState.scenario_id);
        }
    }

    entry = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    Area_RunSetupStream(entry->handler);
    entry = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    if (entry->callback != 0)
        entry->callback();

    SYS_ClearFlag(g_SceneEventFlags, 0x1Cu);
    g_SceneState.mode_02 = 1u;
    Game_UpdateScenario();
    func_801C05AC();

    world_flags = g_Game.walk_flags;
    if ((world_flags & AREA_WALK_MAP_LOADING) != 0) {
        if ((entry_facing & 0x80u) != 0) {
            D_80146260 = 0u;
            func_801BE1B0((u32)(entry_facing & 0x7Fu));
            g_Game.walk_flags &= ~AREA_WALK_ACCEPT_LOCK;
            func_80199440();
        }
    } else if ((g_Game.flags & 0x800u) == 0) {
        if ((world_flags & 0x80u) != 0)
            mode = 1u;
        else if ((world_flags & 0x100u) != 0)
            mode = 2u;
        else if ((world_flags & 0x200u) != 0)
            mode = 3u;
        else {
            if (g_Game.party_size < 2u)
                goto end;
            func_8019FF88(0, entry_x, entry_y);
            if (((g_Game.flags & 0x800u) == 0) && ((g_Game.walk_flags & AREA_WALK_MAP_LOADING) == 0))
                Area_SetCellPalette(g_AreaTargetCellX, g_AreaTargetCellY);
            goto tail;
        }
        func_8019FF88(mode, entry_x, entry_y);
    tail:
        mode = g_Game.party_size;
        if (mode < 2u)
            goto end;
        world_flags       = g_Game.walk_flags;
        g_Game.walk_flags = world_flags | 0x12u;
        if (mode == 3u)
            g_Game.walk_flags = world_flags | 0x16u;
    }
end:
    g_Game.walk_flags &= 0xEE7Fu;
}
#else
INCLUDE_ASM(func_8019FAA0);
#endif

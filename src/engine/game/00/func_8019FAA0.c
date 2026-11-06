#include "game_00.h"

typedef struct GameCopyBlock {
    u8 data[8];
} GameCopyBlock;

#ifdef NON_MATCHING
NON_MATCHING void func_8019FAA0(u16 selection_seed, u32 context_a, u32 context_b, u8 context_kind) {
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

    if ((context_kind & 0x80u) != 0)
        g_AreaWalkFlags |= AREA_WALK_MAP_LOADING;
    else
        g_AreaWalkFlags &= 0x7FFFu;
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
        g_SaveData.snd_bgm_id = 0xFFu;
    else
        SND_StartBgm(seed, 100, 8);

    if (g_GameAreaId != selection_seed) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            g_GameAreaId = selection_seed;
            EMI_LoaderStreamInitSlot((u32)(selection_seed + EMI_SLOT_AREA));
            while (EMI_LoaderIsReady() == 0)
                CallbackWait(1u);
        }
    }

    entry              = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    g_GameRequestFlags = entry->flag_32;
    GFX_ResetPalette();
    g_GfxPalettePending = 1u;

    func_801BFF9C(context_a, context_b, (u32)context_kind);
    D_80143F03 = func_801A0348(D_8014930A, D_8014930E);
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

    if ((LOB(g_SceneState.flags_01) & SCENE_STATE_CHAPTER_ADVANCE) != 0) {
        counter                        = LOBU(g_SceneState.scenario_id);
        LOBU(g_SceneState.scenario_id) = (u8)(counter + 1);
        if ((s8)(counter + 1) == 16) {
            LOBU(g_SceneState.scenario_id) = (u8)(counter + 2);
            Scene_Start(LOBU(g_SceneState.scenario_id));
        }
    }

    entry = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    Area_RunSetupStream(entry->handler);
    entry = (AreaLoad*)g_AreaLoads[g_GameAreaId];
    if (entry->callback != 0)
        entry->callback();

    SYS_ClearFlag(g_SaveData.scene_event_flags, 0x1Cu);
    g_SceneState.mode_02 = 1u;
    Game_RunScenarioEntry();
    func_801C05AC();

    world_flags = g_AreaWalkFlags;
    if ((world_flags & AREA_WALK_MAP_LOADING) != 0) {
        if ((context_kind & 0x80u) != 0) {
            D_80146260 = 0u;
            func_801BE1B0((u32)(context_kind & 0x7Fu));
            g_AreaWalkFlags &= ~AREA_WALK_ACCEPT_LOCK;
            func_80199440();
        }
    } else if ((g_GameFlags & 0x800u) == 0) {
        if ((world_flags & 0x80u) != 0)
            mode = 1u;
        else if ((world_flags & 0x100u) != 0)
            mode = 2u;
        else if ((world_flags & 0x200u) != 0)
            mode = 3u;
        else {
            if (g_PartySize < 2u)
                goto end;
            func_8019FF88(0, context_a, context_b);
            if (((g_GameFlags & 0x800u) == 0) && ((g_AreaWalkFlags & AREA_WALK_MAP_LOADING) == 0))
                Area_SetCellPalette(D_8014930A, D_8014930E);
            goto tail;
        }
        func_8019FF88(mode, context_a, context_b);
    tail:
        mode = g_PartySize;
        if (mode < 2u)
            goto end;
        world_flags     = g_AreaWalkFlags;
        g_AreaWalkFlags = world_flags | 0x12u;
        if (mode == 3u)
            g_AreaWalkFlags = world_flags | 0x16u;
    }
end:
    g_AreaWalkFlags &= 0xEE7Fu;
}
#else
INCLUDE_ASM(func_8019FAA0);
#endif

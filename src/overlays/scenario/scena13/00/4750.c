#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FB390(void* entity) {
    ((Actor*)entity)->unk_7E = (((Actor*)entity)->unk_7E + 1);
}

MATCH void func_801FB3A4(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 3;
    g_ScenarioState.step_05  = 5;
}

MATCH void func_801FB3DC(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 6;
    g_ScenarioState.step_05  = 0x19;
}

MATCH void func_801FB414(void) {
    SYS_SetFlag(g_SceneFlags, 28);
    Scene_StartEvent(44, 0);
    g_SceneEventState.selection = 17;
}

#ifdef NON_MATCHING
NON_MATCHING s32 func_801FB464(s32 x, s32 y) {
    u8 cell_type;

    if (LOHU(g_GameAreaId) == AREA_ID_STEEL_BEACH_FREIGHTER && g_GameCellType == 1 && SYS_TestFlag(g_SceneFlags, 14) == 0 && x == TO_COORD(66) + COORD_HALF && (u32)((y >> 16) - 58) < 2U) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step_05  = 0;
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_RELAY_POINT_A_PORTAL && g_GameCellType == 4 && SYS_TestFlag(g_SceneFlags, 15) == 0 && (u32)((x >> 16) - 54) < 3U && (u32)((y >> 16) - 50) < 4U &&
        g_Game.members[0].facing != 0 && (u32)(g_Game.members[0].facing - 6) >= 2U) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step_05  = 0;
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_STEEL_GRAVE && g_GameCellType == 0 && x == TO_COORD(3) + COORD_HALF && (u32)((y >> 16) - 6) < 3U) {
        SYS_SetFlag(g_SceneFlags, 6);
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DRAGNIER_SURFACE) {
        if (g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 20) == 0 && x == TO_COORD(59) + COORD_HALF && (u32)((y >> 16) - 31) < 4U) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step_05  = 0;
            return 1;
        }
        if (g_GameCellType == 1 && SYS_TestFlag(g_SceneFlags, 29) != 0 && SYS_TestFlag(g_SceneFlags, 30) == 0 && x == TO_COORD(59) + COORD_HALF && (u32)((y >> 16) - 31) < 4U) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 8;
            g_ScenarioState.step_05  = 5;
            return 1;
        }
        if (g_GameCellType == 1 && SYS_TestFlag(g_SceneFlags, 17) == 0 && x == TO_COORD(66) + COORD_HALF && (u32)((y >> 16) - 100) < 3U) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step_05  = 0;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DRAGNIER_ELDER_FIGHT) {
        cell_type = g_GameCellType;
        if (cell_type == 2 && (x >> 16) == 37 && (u32)((y >> 16) - 29) < 2U && (g_Game.members[0].facing == 0 || (u32)(g_Game.members[0].facing - 6) < 2U) && SYS_TestFlag(g_SceneFlags, 27) == 0) {
            Game_SetScriptActive();
            if (SYS_TestFlag(g_SceneFlags, 24) == 0) {
                if (g_Game.members[0].chr.character_id == cell_type) {
                    Scene_SetupParty((u32)g_SceneFlags);
                }
            } else if (SYS_TestFlag(g_SceneFlags, 25) == 0) {
                if (g_Game.members[0].chr.character_id == 8) {
                    Scene_SetupParty(4);
                } else if (g_Game.members[0].chr.character_id == 5) {
                    Scene_SetupParty(3);
                } else {
                    Scene_SetupParty(2);
                }
            } else if (SYS_TestFlag(g_SceneFlags, 26) == 0) {
                if (g_Game.members[0].chr.character_id != 7) {
                    Scene_SetupParty((u32)g_SceneFlags);
                }
            } else if (g_Game.members[0].chr.character_id == 7) {
                Scene_SetupParty((u32)g_SceneFlags);
            }
            g_ScriptVars[0] = 1;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_COLONY_OUTSIDE && SYS_TestFlag(g_SceneEventFlags, 45) != 0 && SYS_TestFlag(g_SceneFlags, 11) == 0 && (u32)((x >> 16) - 10) < 2U && (u32)((y >> 16) - 98) < 3U &&
        (g_Game.members[0].facing == 0 || (u32)(g_Game.members[0].facing - 6) < 2U)) {
        g_ScriptVars[0] = 0;
        Scene_SetupParty(9);
        g_ScenarioState.state_04 = 3;
        g_ScenarioState.step_05  = 20;
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_KOMBINAT_WORLD_MAP && x == TO_COORD(20) + COORD_HALF && (u32)((y >> 16) - 18) < 9U) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 8;
        g_ScenarioState.step_05  = 4;
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_KOMBINAT && g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 2) == 0 && x == TO_COORD(2) + COORD_HALF && (u32)((y >> 16) - 48) < 2U) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 2;
        g_ScenarioState.step_05  = 0;
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801FB464);
#endif

MATCH s32 func_801FBA34(s32 x, s32 y) {
    if (LOHU(g_GameAreaId) == 0x8F && g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 0x1C) != 0 && SYS_TestFlag(g_SceneFlags, 0x1D) == 0 && (x >> 16) == 0x2E && (u32)((y >> 16) - 0x1F) < 4U) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 8;
        g_ScenarioState.step_05  = 0;
        return 1;
    }
    if (LOHU(g_GameAreaId) != 0x91) {
        return 0;
    }
    if (g_GameCellType != 5) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneFlags, 0xA) != 0) {
        return 0;
    }
    if ((u32)((x >> 16) - 0x40) >= 2U) {
        return 0;
    }
    if ((y >> 16) != 0x6A) {
        return 0;
    }
    SYS_SetFlag(g_SceneFlags, 0xA);
    Area_SetCellPalette(0x40, 0x6B);
    return 0;
}

MATCH void Scene_JoinPartyRyuAdultPecoMomo(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_PECO, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_PECO);
    Party_JoinMember(CHAR_ID_MOMO);
}

MATCH void func_801FBBC4(void) {
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        D_80144908[slot] = g_PartyFieldOrder[slot];
        D_8014490B[slot] = g_PartyBattleOrder[slot];
    }
    for (slot = 0; slot < 3; slot++) {
        Party_RemoveMember(D_80144908[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

/* func_801FBC88 */
MATCH void Scene_LoadPartyRyuAdult(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT, 0U);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
}

MATCH void func_801FBCC4(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        ids[slot] = D_80144908[slot];
    }
    EMI_LoadPartyArchives(ids[0], ids[1], ids[2], 0);
    g_Game.party_size = 0;
    Party_JoinMember(ids[0]);
    Party_JoinMember(ids[1]);
    Party_JoinMember(ids[2]);
    for (slot = 3; slot < 6; slot++) {
        g_PartyFieldOrder[slot] = D_80144908[slot];
    }
}

MATCH void Scene_SetPartyRyuAdultMomoNinaAdult(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT);
}

MATCH void func_801FBDD8(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        Party_RemoveMember(ids[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_GARR, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

/* func_801FBE98 */
MATCH void Scene_JoinRei(void) {
    Party_JoinMember(CHAR_ID_REI);
    Party_LoadPalettes();
}

/* func_801FBEC0 */
MATCH void Scene_JoinGarr(void) {
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

MATCH void func_801FBEE8(void) {
}

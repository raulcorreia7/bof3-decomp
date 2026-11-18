#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA08C(void) {
    u8* step = &g_ScenarioState.step_05;

    switch (*step) {
        case 0:
            if (D_8014623B != 2) {
                Scene_SetupParty(0);
                *step = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_SetFlag(g_SceneFlags, 0x13);
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 5:
            if (!(g_InputPressed & g_InputMasks[INPUT_SLOT_MENU]) && g_GameStateIndex == GAME_REQUEST_IDLE) {
                *g_ScriptVars = 0;
                *step         = 6;
                Game_RequestAreaChange(0x76, 0x490000, 0x188000, 0x81);
            }
            break;
        case 6:
            if (*g_ScriptVars == 1 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                *g_ScriptVars = 0;
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801FA1F0(void) {
}
#else
INCLUDE_ASM(func_801FA1F0);
#endif

MATCH void func_801FA8B8(void) {
    u8 slot;

    switch (g_ScenarioState.step_05) {
        case 0:
            if (D_8014623B == 3) {
                break;
            }
            D_80146258 |= 8;
            Scene_SetupParty(5);
            func_801C601C(1);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (*g_ScriptVars != 2) {
                break;
            }
            Scene_SetupParty(6);
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (*g_ScriptVars != 0x25) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != GAME_NONE) {
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x9A;
            }
            g_ScenarioState.step_05 = 3;
            break;
        case 3:
            if (*g_ScriptVars != 0x28) {
                break;
            }
            func_801BFE34(0xE8000, 0xE8000, 0x36);
            func_801C7A54(0x36);
            g_ScenarioState.step_05 = 4;
            break;
        case 4:
            if (*g_ScriptVars != 0x32) {
                break;
            }
            *g_ScriptVars = 0;
            Scene_SetupParty(9);
            UI_SetMode(4);
            g_ScenarioState.step_05 = 5;
            break;
        case 5:
            if (g_UiWindowEffectBusy) {
                break;
            }
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 6;
            SYS_SetFlag(g_SceneFlags, 0x1E);
            func_8019FA28(0x77, 0xA8000, 0xB0000, 0x87);
            g_GamePrevSelection = 0x61;
            break;
        case 6:
            if (*g_ScriptVars != 1) {
                break;
            }
            UI_SetMode(5);
            g_AreaDrawFlags = 0x1F;
            SND_PlaySE(0x20C);
            g_ScenarioState.step_05 = 7;
            break;
        case 7:
            if (g_UiWindowEffectBusy) {
                break;
            }
            *g_ScriptVars           = 2;
            g_ScenarioState.step_05 = 8;
            break;
        case 8:
            if (*g_ScriptVars != 0x0E) {
                break;
            }
            D_80146258 ^= 8;
            goto clear_script_state;
        case 20:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_075, 0x15);
            break;
        case 21:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (*g_ScriptVars != 0x0A) {
                goto clear_script_state;
            }
            Scene_SetupParty(8);
            g_ScenarioState.step_05 = 0x16;
            break;
        case 22:
            if (*g_ScriptVars != 0x19) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x2C);
            goto clear_script_state;
        case 30:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_076, 0x1F);
            break;
        case 31:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            goto clear_script_state;
    }
    return;

clear_script_state:
    Game_ClearScriptActive();
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 0;
}

MATCH void func_801FAC88(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScenarioState.step_05 = 1;
            Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD_HALF(61), TO_COORD(11), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
            break;
        case 1:
            if (g_ScriptVars[0] == 0x0F) {
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                Char_RebuildPartyStats();
                SND_StartXAStream(0, 1);
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0;
                if (SND_IsXAIdle() != 0) {
                    g_ScenarioState.step_05 = 3;
                }
            }
            break;
        case 3:
            g_ScenarioState.step_05 = 4;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_WORLD_MAP, TO_COORD(41), TO_COORD(50), FACING_DOWN_RIGHT);
            break;
        case 4:
            SYS_SetFlag(g_SceneFlags, 0x2E);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            g_GameFlags ^= 0x0E;
            Game_ClearScriptActive();
            *g_ScriptVars = 0;
            Scene_ClearScriptState(&g_ScenarioState.step_05);
            break;
        case 14:
            break;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801FAE0C(void) {
}
#else
INCLUDE_ASM(func_801FAE0C);
#endif

MATCH void func_801FBC78(void) {
    u8* step = &g_ScenarioState.step_05;

    switch (*step) {
        case 0:
            Scene_SetupParty(2);
            *step = 1;
            break;
        case 1:
            if (*g_ScriptVars == 3) {
                SYS_SetFlag(g_SceneFlags, 0x24);
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}

MATCH void func_801FBD0C(void) {
    u8* timer;

    timer = &g_ScenarioState.step_05;
    if (*timer == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Scene_SetupParty(1);
        g_ScenarioState.state_04 = 0;
        *timer                   = 0;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801FBD6C(void) {
}
#else
INCLUDE_ASM(func_801FBD6C);
#endif

MATCH void func_801FC588(void) {
}

MATCH void func_801FC590(void) {
    u8 cam                   = D_801FE430[g_ScenarioState.timer_06 & 3];
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = g_AreaCameraOffsetY + ((cam << 24) >> 22);
}

MATCH void func_801FC5DC(void) {
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FC624(void) {
}

MATCH void func_801FC62C(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 5;
}

MATCH void func_801FC668(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 0;
    g_ScenarioState.step_05  = 5;
    g_ScenarioState.state_04 = 5;
}

MATCH void func_801FC6A4(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 5;
    g_ScenarioState.state_04 = 4;
}

MATCH void func_801FC6DC(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xA;
    g_ScenarioState.step_05  = 0;
}

MATCH void func_801FC710(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xA;
    g_ScenarioState.step_05  = 1;
}

MATCH void func_801FC748(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xD;
    g_ScenarioState.step_05  = 5;
}

MATCH void func_801FC788(void) {
    SYS_SetFlag(g_SceneFlags, 0xEU);
}

MATCH void func_801FC7B0(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 6;
    g_ScenarioState.step_05  = 0x64;
}

MATCH void func_801FC7E8(void) {
    SYS_SetFlag(g_SceneFlags, 0x10U);
}

MATCH void func_801FC810(void) {
    SYS_SetFlag(g_SceneFlags, 0x14U);
}

MATCH void func_801FC838(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 8;
    g_ScenarioState.step_05  = 0xF;
}

MATCH void func_801FC870(void) {
}

MATCH void func_801FC878(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xF;
    g_ScenarioState.step_05  = 0;
}

MATCH void func_801FC8AC(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xF;
    g_ScenarioState.step_05  = 0x14;
}

MATCH void func_801FC8E4(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xF;
    g_ScenarioState.step_05  = 0x28;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801FC91C(void) {
}
#else
INCLUDE_ASM(func_801FC91C);
#endif

MATCH s32 func_801FD278(void) {
    return 0;
}

MATCH s8 func_801FD280(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FE474, 14, D_801FE4BC);
}

MATCH s32 func_801FD2E8(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0x14;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 6;
    return 1;
}

MATCH s32 func_801FD388(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0x1E;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 0;
        g_ScenarioState.state_04 = 6;
        return 1;
    }
}

MATCH s32 func_801FD498(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xF) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0x28;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 0;
        g_ScenarioState.state_04 = 6;
        return 1;
    }
}

MATCH s32 func_801FD5A8(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x12) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x1D) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 50;
            *g_ScriptVars            = 0;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x11) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 7;
            g_ScenarioState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 5;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 0;
        g_ScenarioState.state_04 = 6;
        return 1;
    }
}

MATCH s32 func_801FD6F8(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 6;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        g_AreaSceneMode = 2;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 6;
    return 1;
}

MATCH s32 func_801FD7F4(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 2;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 3;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xF) == 0) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 6;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        g_AreaSceneMode = 3;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 6;
    return 1;
}

MATCH s32 func_801FD8F0(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x18);
    return 1;
}

MATCH s32 func_801FD978(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 1;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x19);
    return 1;
}

MATCH s32 func_801FDA04(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 2;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1A);
    return 1;
}

MATCH s32 func_801FDA90(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 3;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1B);
    return 1;
}

MATCH s32 func_801FDB1C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 5;
        g_ScenarioState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 4;
    g_ScenarioState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1C);
    return 1;
}

MATCH s32 func_801FDBA8(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        SYS_SetFlag(g_SceneFlags, 0x3D);
        SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0x03));
        return 1;
    }

    Game_SetScriptActive();
    g_ScenarioState.step_05  = 6;
    g_ScenarioState.state_04 = 8;
    return 1;
}

MATCH s32 func_801FDC1C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x2C) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 0x14;
        g_ScenarioState.state_04 = 9;
        return 1;
    }
    return -1;
}

MATCH s32 func_801FDC70(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x33) != 0) {
        return -1;
    }
    if (g_Game.members[0].chr.character_id != CHAR_ID_REI) {
        Game_SetScriptActive();
        g_ScenarioState.step_05  = 0x34;
        g_ScenarioState.state_04 = 0x0F;
        return 1;
    }
    *g_ScriptVars = 0;
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0x32;
    g_ScenarioState.state_04 = 0x0F;
    return 1;
}

/* func_801FDCF4 */
MATCH void Scene_JoinAdultNinaWithGarr(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FDD38 */
MATCH void Scene_JoinGarrWithAdultNina(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_JoinAdultNinaMomo.h"

#include "overlays/scenario/Scene_JoinMomo.h"

#include "overlays/scenario/Scene_JoinAdultNina.h"

MATCH void func_801FDE50(void) {
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_PECO);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_JoinMomoPeco.h"

#include "overlays/scenario/Scene_JoinPeco.h"

/* func_801FDF10 */
MATCH void Scene_JoinMomoWithPeco(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_PECO, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RebuildRyuGarrParty.h"

/* func_801FE014 */
MATCH void Scene_JoinAdultNinaWithRei(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE058 */
MATCH void Scene_JoinReiAdultNina(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE0A4 */
MATCH void Scene_JoinReiWithAdultNina(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_REI);
    Party_LoadPalettes();
}

/* func_801FE0E8 */
MATCH void Scene_JoinRyuAdult(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveRei.h"

/* func_801FE154 */
MATCH void Scene_RemoveReiGarr(void) {
    Party_RemoveMember(CHAR_ID_REI);
    Party_RemoveMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveGarr.h"

/* func_801FE1AC */
MATCH void Scene_RemoveGarrAdultNina(void) {
    Party_RemoveMember(CHAR_ID_GARR);
    Party_RemoveMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE1DC */
MATCH void Scene_RemoveReiAdultNina(void) {
    Party_RemoveMember(CHAR_ID_REI);
    Party_RemoveMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveAdultNina.h"

#include "overlays/scenario/Scene_StashPartyExceptRyuAdult.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

#include "overlays/scenario/Scene_RemovePeco.h"

/* func_801FE35C */
MATCH void Scene_RemoveRyuAdult(void) {
    Party_RemoveMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

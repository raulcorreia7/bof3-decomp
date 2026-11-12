#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F73A0(void) {
    Scene_ClearWorkRows();
    func_801F76D0();
    g_Task->timer = 0xFF;
    g_Task->header.mode++;
}

MATCH void func_801F73F0(void) {
    if (!(func_801F75BC() & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801F7424(Actor* actor) {
    POLY_F3* poly;
    FAKE_STACK_PADS(u8, 48);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 0x3C0, 0) & HALF_MASK, 0);
    Area_AddCellPrim(actor->unk_18, actor->unk_1C, 0, sizeof(DR_MODE));
    poly = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(poly);
    SetSemiTrans(poly, 1);
    Area_ProjectPoint(&actor->unk_18, (DVECTOR*)&poly->x0);
    poly->x1 = poly->x0 + D_801FE38C[actor->unk_04].dx1;
    poly->y1 = poly->y0 + D_801FE38C[actor->unk_04].dy1;
    poly->x2 = poly->x0 + D_801FE38C[actor->unk_04].dx2;
    poly->y2 = poly->y0 + D_801FE38C[actor->unk_04].dy2;
    poly->r0 = 0;
    poly->g0 = actor->unk_03;
    poly->b0 = actor->unk_03;
    Area_AddCellPrim(actor->unk_18, actor->unk_1C, -2, sizeof(POLY_F3));
}

/* func_801F7574 */
MATCH void Scene_ClearWorkRows(void) {
    u8* row;
    u8  i;

    row = MEM_PTR(u8, 0x800E5000u) + g_Task->unk_06 * 0x500;
    for (i = 0; i < 32; i++, row += 40) {
        *row = 0;
    }
}

INCLUDE_ASM(func_801F75BC);

INCLUDE_ASM(func_801F76D0);

MATCH void func_801F78D0(void) {
    SYS_DISPATCH_BYTE(D_801FE3E0, D_80146872);
}

MATCH void func_801F790C(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7920);

MATCH void func_801F83D8(void) {
    SYS_DISPATCH_BYTE(D_801FE3EC, g_SceneState.state_04);
}

MATCH void func_801F8414(void) {
}

MATCH void func_801F841C(void) {
    u8* step = &D_80146875;

    switch (*step) {
        case 0:
            *step = 1;
            SYS_SetFlag(g_SceneFlags, 0);
            Game_RequestAreaChange(AREA_ID_EYGNOCK_ROAD, TO_COORD_HALF(31), TO_COORD(76), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
            break;
        case 1:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            *step           = 2;
            break;
        case 2:
            if (*g_ScriptVars == 0x11) {
                SYS_SetFlag(g_SceneFlags, 1);
                Game_ClearScriptActive();
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801F8504);

INCLUDE_ASM(func_801F8770);

INCLUDE_ASM(func_801F8D30);

MATCH void func_801F9354(void) {
    u8* step = &D_80146875;
    u8* vars;

    switch (*step) {
        case 0:
            if (g_GameStateIndex != 2) {
                *g_ScriptVars = 1;
                func_801BE1B0(0xC);
                *step = 1;
            }
            break;
        case 1:
            if (*g_ScriptVars == 9) {
                SYS_SetFlag(g_SceneFlags, 0x3F);
                Game_ClearScriptActive();
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                *step      = 0;
                D_80146874 = 0;
            }
            break;
        case 5:
            if (g_GameStateIndex != 2) {
                *g_ScriptVars = 1;
                *step         = 6;
            }
            break;
        case 6:
            vars = g_ScriptVars;
            if (*vars == 2) {
                Game_ClearScriptActive();
                *vars      = 0;
                D_80146865 = 0;
                D_80146866 = 0;
                D_80146867 = 0;
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801F9498);

MATCH void func_801FA08C(void) {
    u8* step = &D_80146875;

    switch (*step) {
        case 0:
            if (D_8014623B != 2) {
                func_801BE1B0(0);
                *step = 1;
            }
            break;
        case 1:
            if (g_GameStateIndex != 2) {
                SYS_SetFlag(g_SceneFlags, 0x13);
                Game_ClearScriptActive();
                *step      = 0;
                D_80146874 = 0;
            }
            break;
        case 5:
            if (!(g_InputPressed & g_InputMasks[INPUT_SLOT_MENU]) && g_GameStateIndex == 0) {
                *g_ScriptVars = 0;
                *step         = 6;
                Game_RequestAreaChange(0x76, 0x490000, 0x188000, 0x81);
            }
            break;
        case 6:
            if (*g_ScriptVars == 1 && g_GameStateIndex != 2) {
                *g_ScriptVars = 0;
                Game_ClearScriptActive();
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801FA1F0);

INCLUDE_ASM(func_801FA8B8);

MATCH void func_801FAC88(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD_HALF(61), TO_COORD(11), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
            break;
        case 1:
            if (g_ScriptVars[0] == 0x0F) {
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                func_801C16B8();
                SND_StartXAStream(0, 1);
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0;
                if (SND_IsXAIdle() != 0) {
                    g_SceneState.step_05 = 3;
                }
            }
            break;
        case 3:
            g_SceneState.step_05 = 4;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_WORLD_MAP, TO_COORD(41), TO_COORD(50), FACING_DOWN_RIGHT);
            break;
        case 4:
            SYS_SetFlag(g_SceneFlags, 0x2E);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            g_GameFlags ^= 0x0E;
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
        case 14:
            break;
    }
}

INCLUDE_ASM(func_801FAE0C);

MATCH void func_801FBC78(void) {
    u8* step = &D_80146875;

    switch (*step) {
        case 0:
            func_801BE1B0(2);
            *step = 1;
            break;
        case 1:
            if (*g_ScriptVars == 3) {
                SYS_SetFlag(g_SceneFlags, 0x24);
                Game_ClearScriptActive();
                *step      = 0;
                D_80146874 = 0;
            }
            break;
    }
}

MATCH void func_801FBD0C(void) {
    u8* timer;

    timer = &D_80146875;
    if (*timer == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        func_801BE1B0(1);
        D_80146874 = 0;
        *timer     = 0;
    }
}

INCLUDE_ASM(func_801FBD6C);

MATCH void func_801FC588(void) {
}

MATCH void func_801FC590(void) {
    u8 cam                   = D_801FE430[D_80146876 & 3];
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
    g_ScriptVars[0]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC668(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_SceneState.step_05  = 5;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FC6A4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_SceneState.state_04 = 4;
}

MATCH void func_801FC6DC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xA;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FC710(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xA;
    g_SceneState.step_05  = 1;
}

MATCH void func_801FC748(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xD;
    g_SceneState.step_05  = 5;
}

MATCH void func_801FC788(void) {
    SYS_SetFlag(g_SceneFlags, 0xEU);
}

MATCH void func_801FC7B0(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0x64;
}

MATCH void func_801FC7E8(void) {
    SYS_SetFlag(g_SceneFlags, 0x10U);
}

MATCH void func_801FC810(void) {
    SYS_SetFlag(g_SceneFlags, 0x14U);
}

MATCH void func_801FC838(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 8;
    g_SceneState.step_05  = 0xF;
}

MATCH void func_801FC870(void) {
}

MATCH void func_801FC878(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xF;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FC8AC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xF;
    g_SceneState.step_05  = 0x14;
}

MATCH void func_801FC8E4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xF;
    g_SceneState.step_05  = 0x28;
}

INCLUDE_ASM(func_801FC91C);

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
            g_SceneState.step_05  = 0x14;
            g_SceneState.state_04 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            g_SceneState.step_05  = 5;
            g_SceneState.state_04 = 6;
            return 1;
        }
    }
    Game_SetScriptActive();
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 6;
    return 1;
}

MATCH s32 func_801FD388(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            D_80146875 = 2;
            D_80146874 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            D_80146875 = 3;
            D_80146874 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            D_80146875 = 0x1E;
            D_80146874 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            D_80146875 = 5;
            D_80146874 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        D_80146875 = 0;
        D_80146874 = 6;
        return 1;
    }
}

MATCH s32 func_801FD498(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            D_80146875 = 2;
            D_80146874 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            D_80146875 = 3;
            D_80146874 = 6;
            return 1;
        } else if (SYS_TestFlag(g_SceneFlags, 0xF) == 0) {
            Game_SetScriptActive();
            D_80146875 = 0x28;
            D_80146874 = 6;
            return 1;
        } else {
            Game_SetScriptActive();
            D_80146875 = 5;
            D_80146874 = 6;
            return 1;
        }
    } else {
        Game_SetScriptActive();
        D_80146875 = 0;
        D_80146874 = 6;
        return 1;
    }
}

INCLUDE_ASM(func_801FD5A8);

MATCH s32 func_801FD6F8(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xC) == 0) {
            Game_SetScriptActive();
            D_80146875 = 2;
            D_80146874 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xE) == 0) {
            Game_SetScriptActive();
            D_80146875 = 3;
            D_80146874 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            D_80146875 = 6;
            D_80146874 = 6;
            return 1;
        }
        g_AreaSceneMode = 2;
        return 1;
    }
    Game_SetScriptActive();
    D_80146875 = 0;
    D_80146874 = 6;
    return 1;
}

MATCH s32 func_801FD7F4(void) {
    if (D_80145F09 == 5) {
        if (SYS_TestFlag(g_SceneFlags, 0xD) == 0) {
            Game_SetScriptActive();
            D_80146875 = 2;
            D_80146874 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x10) == 0) {
            Game_SetScriptActive();
            D_80146875 = 3;
            D_80146874 = 6;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 0xF) == 0) {
            Game_SetScriptActive();
            D_80146875 = 6;
            D_80146874 = 6;
            return 1;
        }
        g_AreaSceneMode = 3;
        return 1;
    }
    Game_SetScriptActive();
    D_80146875 = 0;
    D_80146874 = 6;
    return 1;
}

MATCH s32 func_801FD8F0(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 5;
        g_SceneState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x18);
    return 1;
}

MATCH s32 func_801FD978(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 5;
        g_SceneState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_SceneState.step_05  = 1;
    g_SceneState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x19);
    return 1;
}

MATCH s32 func_801FDA04(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 5;
        g_SceneState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_SceneState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1A);
    return 1;
}

MATCH s32 func_801FDA90(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 5;
        g_SceneState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_SceneState.step_05  = 3;
    g_SceneState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1B);
    return 1;
}

MATCH s32 func_801FDB1C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 5;
        g_SceneState.state_04 = 8;
        return 1;
    }
    Game_SetScriptActive();
    g_SceneState.step_05  = 4;
    g_SceneState.state_04 = 8;
    SYS_SetFlag(g_SceneFlags, 0x1C);
    return 1;
}

MATCH s32 func_801FDBA8(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x3D) == 0) {
        SYS_SetFlag(g_SceneFlags, 0x3D);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x03));
        return 1;
    }

    Game_SetScriptActive();
    g_SceneState.step_05  = 6;
    g_SceneState.state_04 = 8;
    return 1;
}

MATCH s32 func_801FDC1C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x2C) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 0x14;
        g_SceneState.state_04 = 9;
        return 1;
    }
    return -1;
}

INCLUDE_ASM(func_801FDC70);

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

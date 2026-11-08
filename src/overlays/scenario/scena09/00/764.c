#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7364(void) {
    u8* entity;

    D_801FE384[entity[1]]();
}

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

INCLUDE_ASM(func_801F7424);

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

INCLUDE_ASM(func_801F841C);

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

INCLUDE_ASM(func_801FAC88);

INCLUDE_ASM(func_801FAE0C);

INCLUDE_ASM(func_801FBC78);

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

MATCH void func_801FC5E4(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FE434[index];
    handler(entity, g_SceneFlags);
}

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

INCLUDE_ASM(func_801FD280);

/* blocker: li v1,6 repeated in each branch delay slot; first diff: +0x10 bne targets +0x70 against +0x68. */
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

/* Hint: retail loads li v0,-1 in the flag test branch delay slot before the test; both the == 0 form and the early return put it after. */
INCLUDE_ASM(func_801FDC70);

/* func_801FDCF4 */
MATCH void Scene_AddNinaAdult(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FDD38 */
MATCH void Scene_AddGarr(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_JoinAdultNinaMomo.h"

#include "overlays/scenario/Scene_JoinMomo.h"

#include "overlays/scenario/Scene_JoinAdultNina.h"

/* func_801FDE50 */
MATCH void Scene_AddPeco(void) {
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_PECO);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_JoinMomoPeco.h"

#include "overlays/scenario/Scene_JoinPeco.h"

/* func_801FDF10 */
MATCH void Scene_JoinMomoParty(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_PECO, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RebuildRyuGarrParty.h"

/* func_801FE014 */
MATCH void Scene_AddNinaAdultRei(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE058 */
MATCH void Scene_JoinReiNinaAdult(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE0A4 */
MATCH void Scene_AddRei(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_REI);
    Party_LoadPalettes();
}

/* func_801FE0E8 */
MATCH void Scene_AddRyuAdult(void) {
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
MATCH void Scene_RemoveGarrNina(void) {
    Party_RemoveMember(CHAR_ID_GARR);
    Party_RemoveMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

/* func_801FE1DC */
MATCH void Scene_RemoveReiNina(void) {
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

#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F70BC(void) {
    u8* entity;

    D_801FAEC0[entity[1]]();
    g_AreaCameraRefreshCount = 2;
}

INCLUDE_ASM(func_801F7104);

INCLUDE_ASM(func_801F7178);

INCLUDE_ASM(func_801F7200);

MATCH void func_801F7288(void) {
    SYS_DISPATCH_BYTE(D_801FAEF0, D_80146872);
}

MATCH void func_801F72C4(void) {
    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    D_80146872      = 1;
}

INCLUDE_ASM(func_801F72E4);

MATCH void func_801F7748(void) {
    SYS_DISPATCH_BYTE(D_801FAEFC, g_SceneState.state_04);
}

MATCH void func_801F7784(void) {
}

INCLUDE_ASM(func_801F778C);

INCLUDE_ASM(func_801F7BFC);

INCLUDE_ASM(func_801F7CC8);

INCLUDE_ASM(func_801F7F08);

INCLUDE_ASM(func_801F82D8);

INCLUDE_ASM(func_801F83C8);

INCLUDE_ASM(func_801F8B84);

MATCH void func_801F917C(void) {
}

INCLUDE_ASM(func_801F9184);

INCLUDE_ASM(func_801FA3A4);

MATCH void func_801FA5B8(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FAF24[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FA5F8(void) {
}

MATCH void func_801FA600(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        Game_SetScriptActive();
        D_80146865 = 0;
        D_80146866 = 0;
        D_80146867 = 0;
        D_80146875 = 0;
        D_80146874 = 2;
        SYS_SetFlag(g_SceneFlags, 5U);
    }
}

MATCH void func_801FA674(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 3;
}

MATCH void func_801FA6C0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 5;
}

MATCH void func_801FA70C(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xa;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 3;
}

MATCH void func_801FA75C(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 6;
}

MATCH void func_801FA7A8(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 7;
}

MATCH void func_801FA7F4(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 9;
}

MATCH void func_801FA840(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 9;
}

MATCH void func_801FA890(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 0xa;
}

MATCH void func_801FA8E0(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x14;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 0xb;
}

MATCH void func_801FA930(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 11;
}

MATCH void func_801FA988(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 14;
}

MATCH void func_801FA9D4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x1e;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 0xe;
}

MATCH void func_801FAA24(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x28;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 5;
}

MATCH s32 func_801FAA74(s32 arg0) {
    if (g_GameAreaId == AREA_ID_STEEL_BEACH_MAP) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
            if (arg0 <= 0x160000) {
                if (((g_BattlePartyBattlers[0].facing - 6) < 2U) || (g_BattlePartyBattlers[0].facing == FACING_NW)) {
                    Game_SetScriptActive();
                    D_80146875 = 0;
                    D_80146874 = 1;
                    return 1;
                }
                Game_SetScriptActive();
                D_80146875 = 0x32;
                D_80146874 = 1;
                return 1;
            }
            return 0;
        }
        if (arg0 <= 0x160000) {
            Game_SetScriptActive();
            D_80146875 = 0x3C;
            D_80146874 = 1;
            return 1;
        }
        return 0;
    }
    return 0;
}

MATCH s32 func_801FAB64(void) {
    return 0;
}

MATCH s32 func_801FAB6C(void) {
    return -1;
}

#include "overlays/scenario/Scene_JoinAdultNinaAndMomo.h"

#include "overlays/scenario/Scene_JoinAdultNina.h"

#include "overlays/scenario/Scene_JoinMomo.h"

MATCH void Scene_JoinAdultNinaAndMomo_801FAC48(void) {
    SCENE_JOIN_ADULT_NINA_AND_MOMO();
}

MATCH void func_801FAC94(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_StagePalettes();
}

MATCH void Scene_JoinMomo_801FACD8(void) {
    SCENE_JOIN_MOMO();
}

#include "overlays/scenario/Scene_JoinMomoAndPeco.h"

#include "overlays/scenario/Scene_JoinPeco.h"

#include "overlays/scenario/Scene_JoinReiAndGarr.h"

#include "overlays/scenario/Scene_RemoveRei.h"

#include "overlays/scenario/Scene_RemoveGarr.h"

#include "overlays/scenario/Scene_RemovePeco.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

#include "overlays/scenario/Scene_RemoveAdultNina.h"

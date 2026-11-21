#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA5F8(void) {
}

MATCH void func_801FA600(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        Game_SetScriptActive();
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.step_05  = 0;
        g_ScenarioState.state_04 = 2;
        SYS_SetFlag(g_SceneFlags, 5U);
    }
}

MATCH void func_801FA674(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 3;
}

MATCH void func_801FA6C0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 5;
}

MATCH void func_801FA70C(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0xa;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 3;
}

MATCH void func_801FA75C(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 6;
}

MATCH void func_801FA7A8(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 7;
}

MATCH void func_801FA7F4(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 9;
}

MATCH void func_801FA840(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 5;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 9;
}

MATCH void func_801FA890(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0x14;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 0xa;
}

MATCH void func_801FA8E0(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0x14;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 0xb;
}

MATCH void func_801FA930(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 2;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 11;
}

MATCH void func_801FA988(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 14;
}

MATCH void func_801FA9D4(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0x1e;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 0xe;
}

MATCH void func_801FAA24(void) {
    Game_SetScriptActive();
    g_ScenarioState.step_05  = 0x28;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 5;
}

MATCH s32 func_801FAA74(s32 y) {
    if (g_GameAreaId == AREA_ID_STEEL_BEACH_MAP) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
            if (y <= TO_COORD(22)) {
                if (((g_Game.members[0].facing - 6) < 2U) || (g_Game.members[0].facing == FACING_UP_LEFT)) {
                    Game_SetScriptActive();
                    g_ScenarioState.step_05  = 0;
                    g_ScenarioState.state_04 = 1;
                    return 1;
                }
                Game_SetScriptActive();
                g_ScenarioState.step_05  = 0x32;
                g_ScenarioState.state_04 = 1;
                return 1;
            }
            return 0;
        }
        if (y <= TO_COORD(22)) {
            Game_SetScriptActive();
            g_ScenarioState.step_05  = 0x3C;
            g_ScenarioState.state_04 = 1;
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

#include "overlays/scenario/shared/Scene_JoinAdultNinaMomo.h"

#include "overlays/scenario/shared/Scene_JoinAdultNina.h"

#include "overlays/scenario/shared/Scene_JoinMomo.h"

MATCH void Scene_JoinAdultNinaMomo2(void) {
    SCENE_JOIN_ADULT_NINA_AND_MOMO();
}

/* func_801FAC94 */
#include "overlays/scenario/shared/Scene_JoinMomoWithGarr.h"

MATCH void Scene_JoinMomo2(void) {
    SCENE_JOIN_MOMO();
}

#include "overlays/scenario/shared/Scene_JoinMomoPeco.h"

#include "overlays/scenario/shared/Scene_JoinPeco.h"

#include "overlays/scenario/shared/Scene_JoinReiGarr.h"

#include "overlays/scenario/shared/Scene_RemoveRei.h"

#include "overlays/scenario/shared/Scene_RemoveGarr.h"

#include "overlays/scenario/shared/Scene_RemovePeco.h"

#include "overlays/scenario/shared/Scene_RemoveMomo.h"

#include "overlays/scenario/shared/Scene_RemoveAdultNina.h"

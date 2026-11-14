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

MATCH s32 func_801F7104(void) {
    s32 mode;

    D_801481F8.x             = 0;
    D_801481F8.y             = 0;
    D_801481F8.z             = 0;
    D_801481E8.x             = g_AreaCameraAngle.vx << 16;
    D_801481E8.y             = g_AreaCameraAngle.vy << 16;
    D_801481E8.z             = g_AreaCameraAngle.vz << 16;
    g_AreaCameraRefreshCount = g_Task->timer;
    mode                     = 1;
    g_Task->header.mode      = mode;
    return mode;
}

MATCH void func_801F7178(void) {
    u16 angle;
    s16 scroll;

    angle                = (u16)g_AreaCameraAngle.vy;
    scroll               = angle + 244;
    g_AreaCameraAngle.vy = angle + 4;
    Area_AdvanceScroll(scroll);
    if (g_AreaCameraAngle.vy >= 241) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        }
        g_Task->header.mode = 2;
    }
}

MATCH void func_801F7200(void) {
    u16 angle;
    s16 scroll;

    angle                = (u16)g_AreaCameraAngle.vy;
    scroll               = angle + 236;
    g_AreaCameraAngle.vy = angle - 4;
    Area_AdvanceScroll(scroll);
    if (g_AreaCameraAngle.vy < -240) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        }
        g_Task->header.mode = 1;
    }
}

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

MATCH void func_801F7BFC(void) {
    u8* state;
    s32 next;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            next            = 1;
            g_ScriptVars[0] = next;
            func_801BE1B0(0);
            *state = next;
            break;
        case 1:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 5);
            Game_ClearScriptActive();
            Scene_ClearScriptState(state);
            break;
    }
}

INCLUDE_ASM(func_801F7CC8);

INCLUDE_ASM(func_801F7F08);

MATCH void func_801F82D8(s32 slot) {
    Actor* work;
    Actor* other;

    TASK_SET(&g_SpawnedActors[slot & BYTE_MASK]);
    Area_SelectSceneRecord(0x18);

    g_Task->active_flags = 0;
    g_Task->unk_2A       = 0;
    g_Task->unk_2B       = (g_Task->unk_2B + 1);
    g_Task->unk_48       = 0;

    work                     = g_Task;
    work->tint.bytes.unk_5D  = 0;
    other                    = g_Task;
    work->vz                 = 0;
    work->gravity            = -8;
    other->tint.bytes.unk_5E = 0;

    g_Task->tint.bytes.unk_5F = 0;
    Actor_SelectScript(0xE);

    g_Task->header.mode = 3;
    g_Task->header.step = 1;
}

INCLUDE_ASM(func_801F83C8);

INCLUDE_ASM(func_801F8B84);

MATCH void func_801F917C(void) {
}

INCLUDE_ASM(func_801F9184);

INCLUDE_ASM(func_801FA3A4);

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FA5F8(void) {
}

MATCH void func_801FA600(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        Game_SetScriptActive();
        g_ScriptVars[1]       = 0;
        g_ScriptVars[2]       = 0;
        g_ScriptVars[3]       = 0;
        g_SceneState.step_05  = 0;
        g_SceneState.state_04 = 2;
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

MATCH s32 func_801FAA74(s32 y) {
    if (g_GameAreaId == AREA_ID_STEEL_BEACH_MAP) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
            if (y <= TO_COORD(22)) {
                if (((g_Game.members[0].facing - 6) < 2U) || (g_Game.members[0].facing == FACING_UP_LEFT)) {
                    Game_SetScriptActive();
                    g_SceneState.step_05  = 0;
                    g_SceneState.state_04 = 1;
                    return 1;
                }
                Game_SetScriptActive();
                g_SceneState.step_05  = 0x32;
                g_SceneState.state_04 = 1;
                return 1;
            }
            return 0;
        }
        if (y <= TO_COORD(22)) {
            Game_SetScriptActive();
            g_SceneState.step_05  = 0x3C;
            g_SceneState.state_04 = 1;
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

#include "overlays/scenario/Scene_JoinAdultNinaMomo.h"

#include "overlays/scenario/Scene_JoinAdultNina.h"

#include "overlays/scenario/Scene_JoinMomo.h"

MATCH void Scene_JoinAdultNinaMomo2(void) {
    SCENE_JOIN_ADULT_NINA_AND_MOMO();
}

/* func_801FAC94 */
#include "overlays/scenario/Scene_JoinMomoWithGarr.h"

MATCH void Scene_JoinMomo2(void) {
    SCENE_JOIN_MOMO();
}

#include "overlays/scenario/Scene_JoinMomoPeco.h"

#include "overlays/scenario/Scene_JoinPeco.h"

#include "overlays/scenario/Scene_JoinReiGarr.h"

#include "overlays/scenario/Scene_RemoveRei.h"

#include "overlays/scenario/Scene_RemoveGarr.h"

#include "overlays/scenario/Scene_RemovePeco.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

#include "overlays/scenario/Scene_RemoveAdultNina.h"

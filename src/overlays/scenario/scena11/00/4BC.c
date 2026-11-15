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

    work                        = g_Task;
    work->tint.bytes.rgb.red    = 0;
    other                       = g_Task;
    work->vz                    = 0;
    work->gravity               = -8;
    other->tint.bytes.rgb.green = 0;

    g_Task->tint.bytes.rgb.blue = 0;
    Actor_SelectScript(0xE);

    g_Task->header.mode = 3;
    g_Task->header.step = 1;
}

INCLUDE_ASM(func_801F83C8);

INCLUDE_ASM(func_801F8B84);

MATCH void func_801F917C(void) {
}

INCLUDE_ASM(func_801F9184);

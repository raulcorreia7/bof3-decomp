#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F90C0(void) {
    u8 count;
    u8 id;

    switch (g_SceneState.step_05) {
        case 0:
            func_801BE1B0(3);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_SceneState.step_05 = 2;
            g_ScriptVars[2]      = 2;
            SYS_SetFlag(g_SceneFlags, 0x12);
            func_8019FA28(0x5E, 0x2E0000, 0x2E0000, 0x84);
            break;
        case 2:
            Message_StartAreaMessage(0x38);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 3;
            break;
        case 3:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_SetMode(5);
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 4;
            break;
        case 4:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0]      = 1;
            g_SceneState.step_05 = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            id                     = func_8019601C();
            D_1F800000.view.raw[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -0x210;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 0x2F2;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x14;
                g_ScriptVars[0]                                     = 3;
                g_SceneState.step_05                                = 6;
            }
            break;
        case 6:
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ -= 0x40;
            count           = g_ScriptVars[3] + 1;
            g_ScriptVars[3] = count;
            if (count < 0x12) {
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_SceneState.step_05     = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 0x13) {
                break;
            }
            func_801C601C(0);
            id                     = func_8019601C();
            D_1F800000.view.raw[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags                       = 1;
                g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = -0x2AA;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 0x200;
                g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x1E;
                g_SceneState.step_05                                = 8;
                g_ScriptVars[3]                                     = D_1F800000.view.raw[0];
            }
            break;
        case 8:
            if (g_ActorSlots[g_ScriptVars[3]].header.flags == 0) {
                g_ScriptVars[0]      = 0x14;
                g_SceneState.step_05 = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] != 0x16) {
                break;
            }
            g_SceneState.step_05 = 0xA;
            SYS_SetFlag(g_SceneFlags, 0x13);
            func_8019FA28(0x5E, 0x2C0000, 0x290000, 0x85);
            g_GamePrevSelection = 0x42;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x22) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x10);
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 20:
            func_801BE1B0(6);
            func_801C601C(1);
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_AreaCameraStep     = 0x20;
            g_SceneState.step_05 = 0x16;
            g_AreaScrollTargetX  = g_Game.members[0].pos.x.fixed;
            g_AreaScrollTargetY  = g_Game.members[0].pos.y.fixed;
            break;
        case 22:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[0]      = 5;
            g_SceneState.step_05 = 0x17;
            break;
        case 23:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            Party_AddZenny(1000, 0);
            g_ScriptVars[0]      = 8;
            g_SceneState.step_05 = 0x18;
            break;
        case 24:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x14);
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 30:
            g_SceneState.step_05 = 0x1F;
            func_8019FA28(0x5E, 0x520000, 0x330000, 0x8E);
            break;
        case 31:
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 0x20;
            break;
        case 32:
            if (g_ScriptVars[0] != 0x36) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}

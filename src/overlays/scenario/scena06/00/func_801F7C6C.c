#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7C6C(void) {
    u8 slot;

    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                func_801BE1B0(3);
                g_SceneState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 4) {
                SYS_SetFlag(g_SceneFlags, 4);
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 5:
            Message_StartAreaMessage(0x42);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 6;
            break;
        case 6:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0xF;
                switch (g_Game.members[0].facing) {
                    case 2:
                        func_801BE1B0(4);
                        g_SceneState.step_05 = 0xB;
                        break;
                    case 3:
                        func_801BE1B0(5);
                        g_SceneState.step_05 = 0xB;
                        break;
                    case 4:
                        func_801BE1B0(6);
                        g_SceneState.step_05 = 0xB;
                        break;
                }
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 0x14) {
                SYS_SetFlag(g_SceneFlags, 5);
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 15:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0x19;
                func_801BE1B0(8);
                g_SceneState.step_05 = 0x10;
            }
            break;
        case 16:
            if (g_ScriptVars[0] == 0x1A) {
                slot                     = Actor_FindFreeSlot();
                D_1F800000.view.raw[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_ActorSlots[slot].header.flags                       = 1;
                    g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 0x3C;
                    g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x3C;
                    g_SceneState.step_05                                = 0x11;
                    g_ScriptVars[1]                                     = D_1F800000.view.raw[0];
                }
            }
            break;
        case 17:
            if (g_ActorSlots[g_ScriptVars[1]].header.flags == 0) {
                g_ScriptVars[0]      = 0x1B;
                g_ScriptVars[1]      = 0;
                g_SceneState.step_05 = 0x12;
            }
            break;
        case 18:
            if (g_ScriptVars[0] == 0x1C) {
                slot                     = Actor_FindFreeSlot();
                D_1F800000.view.raw[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_ActorSlots[slot].header.flags                       = 1;
                    g_ActorSlots[D_1F800000.view.raw[0]].type           = 0x13;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.x = g_AreaCameraAngle.vx;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_ActorSlots[D_1F800000.view.raw[0]].camera_angle.z = 0x200;
                    g_ActorSlots[D_1F800000.view.raw[0]].layer          = 0x3C;
                    g_SceneState.step_05                                = 0x13;
                }
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0x1E) {
                SYS_SetFlag(g_SceneFlags, 7);
                Game_ClearScriptActive();
                g_ScriptVars[0]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}

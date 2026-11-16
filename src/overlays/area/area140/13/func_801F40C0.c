#include "area140_13.h"

MATCH void func_801F40C0(void) {
    s32  active;
    u16  flags;
    u16* held;
    u16  input;
    u16  low_buttons;
    u8   button_index;

    switch (g_SceneEventState.step) {
        case 0:
            active = 1;
            Game_ClearScriptActive();
            Scene_SetupParty(0);
            flags                    = g_GameFlags;
            g_Game.members[0].unk_48 = active;
            g_GameFlags              = flags | 0x1270;
            SYS_SetFlag(g_SceneEventFlags, 102);
            g_SceneEventState.step = active;
            break;
        case 1:
            if (g_AreaCameraOffsetZ != 1664) {
                g_AreaCameraOffsetZ += 64;
            } else {
                g_SceneEventState.step = 2;
            }
            g_AreaCameraRefreshCount = 2;
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                held                                          = &g_InputHeld;
                input                                         = *held;
                low_buttons                                   = input & 0x0FFF;
                ((Area140InputSnapshot*)&D_1F800000)->buttons = input;
                button_index                                  = input >> 12;
                *held                                         = low_buttons;
                low_buttons |= D_801F47C4[0x2B0 + button_index] << 12;
                *held = low_buttons;
            }
            break;
        case 5:
            g_ScriptVars[3]        = 1;
            g_SceneEventState.step = 6;
            break;
        case 6:
            if (g_AreaCameraOffsetZ != 0) {
                g_AreaCameraOffsetZ -= 64;
            } else {
                g_SceneEventState.step = 7;
            }
            Game_SetScriptActive();
            g_AreaCameraRefreshCount = 2;
            break;
        case 7:
            Game_ClearScriptActive();
            flags                    = g_GameFlags;
            g_Game.members[0].unk_48 = 0;
            g_GameFlags              = flags & 0xED8F;
            SYS_ClearFlag(g_SceneEventFlags, 102);
            func_801B3CCC(0);
            g_SceneEventState.mode = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            break;
        case 10:
            MESSAGE_START_WAIT(1);
            g_SceneEventState.step = 11;
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
    }
}

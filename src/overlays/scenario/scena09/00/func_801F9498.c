#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9498(void) {
    u8* game_state_index;
    u8* script_vars;

    switch (g_ScenarioState.step) {
        case 0:
            UI_MessageStartArea(0xA);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 2:
            UI_MessageStartArea(0xB);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 1;
            break;
        case 3:
            UI_MessageStartArea(0xD);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 1;
            break;
        case 5:
            UI_MessageStartArea(0xC);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 1;
            break;
        case 6:
            UI_MessageStartArea(0xF);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 1;
            break;
        case 7:
            UI_MessageStartArea(0x2B);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 8;
            break;
        case 8:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 0xA) {
                    g_ScenarioState.step = 9;
                } else if (g_ScriptVars[0] == 0x14) {
                    g_ScenarioState.step = 0xA;
                }
            }
            break;
        case 9:
            g_ScriptVars[0] = 0;
            Game_ClearScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 10:
            SYS_SetFlag(g_SceneFlags, 0x11);
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 20:
            func_801BE1B0(3);
            g_ScenarioState.step = 0x15;
            break;
        case 21:
            if (g_ScriptVars[0] == 1) {
                g_ScenarioState.step = 0x16;
                Game_RequestAreaChange(0x75, 0x38000, 0x158000, 0x84);
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 2) {
                g_ScenarioState.step = 0x17;
                Game_RequestAreaChange(0x75, 0x560000, 0x2E0000, 0x85);
            }
            break;
        case 23:
            if (g_ScriptVars[0] == 0xF) {
                g_ScenarioState.step = 0x18;
                Game_RequestAreaChange(0x75, 0x38000, 0x150000, 0x86);
            }
            break;
        case 24:
            g_AreaSceneMode = 1;
            SYS_SetFlag(g_SceneFlags, 0xC);
            g_ScenarioState.step = 0x19;
            break;
        case 25:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[0]      = 0;
                g_ScenarioState.step = 0x1A;
                Game_RequestAreaChange(0x75, 0x560000, 0x2E0000, 0x87);
            }
            break;
        case 26:
            if (g_ScriptVars[0] == 4) {
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 30:
            func_801BE1B0(8);
            g_ScenarioState.step = 0x1F;
            break;
        case 31:
            if (g_ScriptVars[0] == 1) {
                UI_ModeSet(0);
                g_ScenarioState.step = 0x20;
            }
            break;
        case 32:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 0x21;
                Game_RequestAreaChange(0x76, 0x70000, 0x118000, 0x83);
            }
            break;
        case 33:
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x3B2;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x38C;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 4;
                g_ScenarioState.step                                        = 0x22;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        case 34:
            if (g_SpawnedActors[g_ScriptVars[3]].header.flags == 0) {
                g_ScriptVars[3] = 0;
                g_ScriptVars[0] = 1;
                UI_ModeSet(5);
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 0x23;
            }
            break;
        case 35:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaSceneMode = 2;
                SYS_SetFlag(g_SceneFlags, 0xD);
                g_ScenarioState.step = 0x24;
            }
            break;
        case 36:
            if (g_ScriptVars[0] == 2) {
                g_AreaDrawFlags      = 0x1F;
                g_ScriptVars[0]      = 0;
                g_ScenarioState.step = 0x25;
                Game_RequestAreaChange(0x75, 0x560000, 0x2B0000, 0x89);
            }
            break;
        case 37:
            if (g_ScriptVars[0] == 9) {
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 40:
            func_801BE1B0(0xA);
            g_ScenarioState.step = 0x29;
            break;
        case 41:
            if (g_ScriptVars[0] == 1) {
                UI_ModeSet(4);
                g_ScenarioState.step = 0x2A;
            }
            break;
        case 42:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 0x2B;
                Game_RequestAreaChange(0x76, 0x88000, 0x78000, 0x83);
            }
            break;
        case 43:
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x31E;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 4;
                g_ScenarioState.step                                        = 0x2C;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        case 44:
            if (g_SpawnedActors[g_ScriptVars[3]].header.flags == 0) {
                g_ScriptVars[3] = 0;
                g_ScriptVars[0] = 1;
                UI_ModeSet(5);
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 0x2D;
            }
            break;
        case 45:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaSceneMode = 3;
                SYS_SetFlag(g_SceneFlags, 0xF);
                g_ScenarioState.step = 0x2E;
            }
            break;
        case 46:
            if (g_ScriptVars[0] == 2) {
                g_ScriptVars[0]      = 0;
                g_ScenarioState.step = 0x2F;
                Game_RequestAreaChange(0x75, 0x530000, 0x300000, 0x8B);
            }
            break;
        case 47:
            if (g_ScriptVars[0] == 8) {
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 50:
            UI_MessageStartArea(0x2B);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 0x33;
            break;
        case 51:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 0xA) {
                    func_801BE1B0(0xC);
                    g_ScenarioState.step = 0x34;
                } else if (g_ScriptVars[0] == 0x14) {
                    g_ScenarioState.step = 0x35;
                }
            }
            break;
        case 52:
            if (g_ScriptVars[0] == 1) {
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 53:
            UI_ModeSet(0);
            g_ScenarioState.step = 0x36;
            break;
        case 54:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]      = 1;
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 0x37;
                Game_RequestAreaChange(0x76, 0x78000, 0x38000, 0x83);
            }
            break;
        case 55:
            UI_ModeSet(5);
            g_AreaDrawFlags      = 0x1F;
            g_ScenarioState.step = 0x38;
            break;
        case 56:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaSceneMode = 4;
                SYS_SetFlag(g_SceneFlags, 0x11);
                SYS_SetFlag(g_SceneFlags, 0x1D);
                g_ScenarioState.step = 0x39;
            }
            break;
        case 57:
            if (g_ScriptVars[0] == 2) {
                g_ScriptVars[0]      = 0;
                g_ScenarioState.step = 0x3A;
                Game_RequestAreaChange(0x75, 0x530000, 0x290000, 0x8D);
            }
            break;
        case 58:
            if (g_ScriptVars[0] == 7) {
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 100:
            game_state_index = &g_GameStateIndex;
            if (*game_state_index != GAME_REQUEST_MESSAGE) {
                UI_MessageStartArea(0x1B);
                *game_state_index    = GAME_REQUEST_MESSAGE;
                g_ScenarioState.step = 0x65;
            }
            break;
        case 101:
            script_vars = g_ScriptVars;
            if (script_vars[0] == 0x64) {
                script_vars[0]       = 0;
                g_ScenarioState.step = 0x66;
                UI_ModeSet(0xD);
                func_801C16B8();
                SND_SeqFadeOut(0, 0, 4, 0x1E);
            } else if (script_vars[0] == 0x65) {
                script_vars[0] = 0;
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 102:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 0x67;
            break;
        case 103:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                if (SND_XAIsIdle()) {
                    g_ScenarioState.step = 0x68;
                }
            }
            break;
        case 104:
            UI_ModeSet(0xE);
            g_AreaDrawFlags      = 0x1F;
            g_ScenarioState.step = 0x69;
            break;
        case 105:
            if (g_UiWindowEffectBusy == 0) {
                SND_BGMPlay(0x61, 0x64, 8);
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}

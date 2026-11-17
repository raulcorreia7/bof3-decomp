#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FA010(void) {
    u8 i;
    u8 message_index;
    u8 slot;

    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVars[0]      = 10;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 11) {
                if (SYS_TestFlag(g_SceneFlags, 15) != 0) {
                    if (func_801FA5EC() != 0) {
                        message_index        = 0x28;
                        g_SceneState.step_05 = 3;
                    } else {
                        message_index        = 0x27;
                        g_SceneState.step_05 = 2;
                    }
                } else {
                    message_index        = 0x26;
                    g_SceneState.step_05 = 2;
                }
                Message_StartAreaMessage(message_index);
                g_GameStateIndex = 2;
            }
            break;
        case 2:
            if (g_GameStateIndex != 2) {
                g_ScriptVars[0] = 0;
                goto clear_script;
            }
            break;
        case 3:
            if (g_GameStateIndex != 2) {
                slot       = Actor_FindFreeSpawned();
                D_801FE9D8 = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags = 1;
                    g_SpawnedActors[slot].type         = 0x5E;
                    g_SpawnedActors[slot].unk_06       = 0x4E;
                    g_SpawnedActors[slot].unk_07       = 3;
                    g_SceneState.step_05               = 4;
                }
            }
            break;
        case 4:
            if ((g_SpawnedActors[D_801FE9D8].header.flags & 1) == 0) {
                if (func_801FA644() != 0) {
                    for (i = 0; i < 8; i++) {
                        D_80144908[i] = 0;
                    }
                    Scene_SetupParty(4);
                    SYS_SetFlag(g_SceneFlags, 17);
                    g_SceneState.step_05 = 6;
                } else {
                    g_ScriptVars[0]      = 20;
                    g_SceneState.step_05 = 5;
                }
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0) {
                g_SceneState.state_04 = 6;
                g_SceneState.step_05  = 0;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 21) {
                slot       = Actor_FindFreeSpawned();
                D_801FE9D8 = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags = 1;
                    g_SpawnedActors[slot].type         = 0x5D;
                    g_SpawnedActors[slot].unk_06       = 0x4E;
                    g_SpawnedActors[slot].unk_07       = 3;
                    g_SceneState.step_05               = 9;
                }
            }
            break;
        case 8:
            if (g_SpawnedActors[D_801FE9D8].header.flags == 0) {
                g_ScriptVars[0]      = 2;
                g_SceneState.step_05 = 9;
            }
            break;
        case 9:
            Scene_SetupParty(3);
            SYS_SetFlag(g_SceneFlags, 13);
            goto clear_script;
        case 10:
            UI_SetMode(0);
            g_SceneState.step_05 = 21;
            break;
        case 20:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                SYS_ThreadWait(1);
                Scene_RunScenario(0);
                g_GameStateIndex     = 6;
                g_SceneState.step_05 = 22;
            }
            break;
        case 21:
            if (g_GameStateIndex == 0) {
                Game_RequestAreaChange(0x58, 0x280000, 0x220000, 1);
                g_GameRequestKind    = GAME_NONE;
                g_GameEntryMode      = GAME_NONE;
                g_SceneState.step_05 = 23;
            }
            break;
        case 22:
            if (g_GameStateIndex == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(0xB);
                g_SceneState.step_05 = 24;
            }
            break;
        case 23:
            if (g_GameStateIndex == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(0xB);
                g_SceneState.step_05 = 24;
            }
            break;
        case 24:
            if (g_UiWindowEffectBusy == 0) {
                SYS_SetFlag(g_SceneFlags, 14);
                Game_ClearScriptActive();
                g_AreaDrawFlags       = 0x1F;
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
            }
            break;
        case 28:
            if (SYS_TestFlag(g_SceneFlags, 15) == 0) {
                Game_ClearScriptActive();
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
                Scene_SetupParty(7);
            } else {
                Scene_SetupParty(8);
                g_SceneState.step_05 = 31;
            }
            break;
        case 29:
            if (g_ScriptVars[0] == 14) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 16);
                Game_RequestAreaChange(0x4B, 0x380000, 0x2C8000, 7);
                g_ScriptVars[0]       = 0;
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
            }
            break;
        case 30:
        case 31:
            break;
    }
    return;

clear_script:
    g_SceneState.state_04 = 0;
    g_SceneState.step_05  = 0;
    Game_ClearScriptActive();
}
#else
INCLUDE_ASM(func_801FA010);
#endif

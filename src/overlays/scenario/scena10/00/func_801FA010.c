#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The scene's opening message handshake, its spawned actors and the map transition. */
MATCH void func_801FA010(void) {
    u8 i;
    u8 message_index;
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            g_ScriptVars[0]      = 10;
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 11) {
                if (SYS_TestFlag(g_SceneFlags, 15) != 0) {
                    if (func_801FA5EC() != 0) {
                        message_index        = 0x28;
                        g_ScenarioState.step = 3;
                    } else {
                        message_index        = 0x27;
                        g_ScenarioState.step = 2;
                    }
                } else {
                    message_index        = 0x26;
                    g_ScenarioState.step = 2;
                }
                UI_MessageStartArea(message_index);
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
                    g_SpawnedActors[D_801FE9D8].type   = 0x5E;
                    g_ScenarioState.step               = 4;
                }
            }
            break;
        case 4:
            if ((g_SpawnedActors[D_801FE9D8].header.flags & 1) == 0) {
                if ((func_801FA644() & 0xFF) != 0) {
                    for (i = 0; i < 8; i++) {
                        D_80144908[i] = 0;
                    }
                    Scene_SetupParty(4);
                    SYS_SetFlag(g_SceneFlags, 17);
                    g_ScenarioState.step = 6;
                } else {
                    g_ScriptVars[0]      = 20;
                    g_ScenarioState.step = 5;
                }
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0) {
                g_ScenarioState.state_04 = 6;
                goto step_zero;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 21) {
                slot       = Actor_FindFreeSpawned();
                D_801FE9D8 = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags = 1;
                    g_SpawnedActors[D_801FE9D8].type   = 0x5D;
                    g_SpawnedActors[D_801FE9D8].unk_06 = 0x4E;
                    g_SpawnedActors[D_801FE9D8].unk_07 = 3;
                }
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            if (g_SpawnedActors[D_801FE9D8].header.flags == 0) {
                g_ScenarioState.step = 2;
            }
            break;
        case 10:
            Scene_SetupParty(3);
            SYS_SetFlag(g_SceneFlags, 13);
        clear_script:
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            Game_ClearScriptActive();
            break;
        case 20:
            UI_ModeSet(0);
            g_ScenarioState.step = 21;
            break;
        case 21:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                SYS_ThreadWait(1);
                Scene_RunScenario(0);
                g_GameStateIndex     = 6;
                g_ScenarioState.step = 22;
            }
            break;
        case 22:
            if (g_GameStateIndex == 0) {
                Game_RequestAreaChange(0x58, 0x280000, 0x220000, 1);
                g_GameRequestType    = GAME_NONE;
                g_GameEntryMode      = GAME_NONE;
                g_ScenarioState.step = 23;
            }
            break;
        case 23:
            if (g_GameStateIndex == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(0xB);
                g_ScenarioState.step = 24;
            }
            break;
        case 24:
            if (g_UiWindowEffectBusy == 0) {
                SYS_SetFlag(g_SceneFlags, 14);
                Game_ClearScriptActive();
                g_AreaDrawFlags = 0x1F;
                goto state_zero;
            }
            break;
        case 30:
            if (SYS_TestFlag(g_SceneFlags, 15) == 0) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                Scene_SetupParty(7);
            } else {
                Scene_SetupParty(8);
                g_ScenarioState.step = 31;
            }
            break;
        case 31:
            if (g_ScriptVars[0] == 14) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 16);
                Game_RequestAreaChange(0x4B, 0x380000, 0x2C8000, 7);
                g_ScriptVars[0] = 0;
                goto state_zero;
            }
            break;
    }
    return;

state_zero:
    g_ScenarioState.state_04 = 0;
step_zero:
    g_ScenarioState.step = 0;
}

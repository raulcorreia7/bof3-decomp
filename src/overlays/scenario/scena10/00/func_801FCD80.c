#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FCD80(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_ScriptVars[0] == 4) {
                SYS_SetFlag(g_SceneFlags, 0x38);
                func_8019FA28(0x78, TO_COORD(32) + COORD_HALF, TO_COORD(115) + COORD_HALF, 0x81);
                g_GamePrevSelection  = 0x7B;
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0) {
                SYS_SetFlag(g_SceneFlags, 0x39);
                g_GameFlags |= 0x10;
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x3A);
                g_GameFlags &= ~0x10;
                func_801BE1B0(3);
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 8:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_SetScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x3B);
                g_GameFlags &= ~0x10;
                func_801C1E3C(3);
                func_801BE1B0(4);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 10:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA10_058, 11);
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 15:
            g_ScriptVars[0] = 10;
            func_801BE1B0(5);
            g_ScenarioState.step = 16;
            break;
        case 16:
            if (g_ScriptVars[0] == 0xE) {
                slot = func_8019601C();
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags = 1;
                    g_SpawnedActors[slot].type         = 0x43;
                }
                g_ScenarioState.timer_06 = 180;
                g_ScenarioState.step     = 17;
            }
            break;
        case 17:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.timer_06 = 1;
                g_ScenarioState.step     = 18;
                g_ScriptVars[0]++;
            }
            break;
        case 18:
            if (--g_ScenarioState.timer_06 == 0) {
                g_AreaDrawMode           = GFX_LAYER_BATTLE_SCENE;
                D_8014933F               = 0;
                g_AreaCameraRefreshCount = 2;
                g_ScenarioState.step     = 19;
                g_ScriptVars[0]++;
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0x13) {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x23);
                func_801C7A54(0x23);
                g_ScenarioState.step = 20;
            }
            break;
        case 21:
            SYS_SetFlag(g_SceneFlags, 0x3C);
            func_8019FA28(0x78, TO_COORD(31) + COORD_HALF, TO_COORD(116) + COORD_HALF, 7);
            g_GameRequestType    = 0xFF;
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0x49;
            g_ScriptVars[0]      = 0;
            g_ScenarioState.step = 22;
            break;
        case 22:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_ScenarioState.step = 23;
            }
            break;
        case 23:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.step = 24;
            }
            break;
        case 24:
            if (g_ScriptVars[0] == 0xC) {
                slot = func_8019601C();
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags = 1;
                    g_SpawnedActors[slot].type         = 0x6B;
                }
                g_ScenarioState.step = 25;
            }
            break;
        case 25:
            if (g_ScriptVars[0] == 0) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                SYS_SetFlag(g_SceneFlags, 0x3D);
            }
            break;
    }
}

#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA8B8(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (D_8014623B == 3) {
                break;
            }
            D_80146258 |= 8;
            Scene_SetupParty(5);
            func_801C601C(1);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (*g_ScriptVars != 2) {
                break;
            }
            Scene_SetupParty(6);
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (*g_ScriptVars != 0x25) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if (slot != GAME_NONE) {
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x9A;
            }
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (*g_ScriptVars != 0x28) {
                break;
            }
            func_801BFE34(0xE8000, 0xE8000, 0x36);
            func_801C7A54(0x36);
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (*g_ScriptVars != 0x32) {
                break;
            }
            *g_ScriptVars = 0;
            Scene_SetupParty(9);
            UI_ModeSet(4);
            g_ScenarioState.step = 5;
            break;
        case 5:
            if (g_SysThreads[2].state) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_ScenarioState.step = 6;
            SYS_SetFlag(g_SceneFlags, 0x1E);
            func_8019FA28(0x77, 0xA8000, 0xB0000, 0x87);
            g_GamePrevSelection = 0x61;
            break;
        case 6:
            if (*g_ScriptVars != 1) {
                break;
            }
            UI_ModeSet(5);
            g_AreaDrawFlags = 0x1F;
            SND_SEPlay(0x20C);
            g_ScenarioState.step = 7;
            break;
        case 7:
            if (g_SysThreads[2].state) {
                break;
            }
            *g_ScriptVars        = 2;
            g_ScenarioState.step = 8;
            break;
        case 8:
            if (*g_ScriptVars != 0x0E) {
                break;
            }
            D_80146258 ^= 8;
            goto clear_script_state;
        case 20:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_075, 0x15);
            break;
        case 21:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (*g_ScriptVars != 0x0A) {
                goto clear_script_state;
            }
            Scene_SetupParty(8);
            g_ScenarioState.step = 0x16;
            break;
        case 22:
            if (*g_ScriptVars != 0x19) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x2C);
            goto clear_script_state;
        case 30:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA09_076, 0x1F);
            break;
        case 31:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            goto clear_script_state;
    }
    return;

clear_script_state:
    Game_ClearScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 0;
}

MATCH void func_801FAC88(void) {
    switch (g_ScenarioState.step) {
        case 0:
            g_ScenarioState.step = 1;
            Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD_HALF(61), TO_COORD(11), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
            break;
        case 1:
            if (g_ScriptVars[0] == 0x0F) {
                UI_ModeSet(UI_MODE_LONG_FADE_OUT);
                Char_RebuildPartyStats();
                SND_XAStartStream(0, 1);
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0;
                if (SND_XAIsIdle() != 0) {
                    g_ScenarioState.step = 3;
                }
            }
            break;
        case 3:
            g_ScenarioState.step = 4;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_WORLD_MAP, TO_COORD(41), TO_COORD(50), FACING_DOWN_RIGHT);
            break;
        case 4:
            SYS_SetFlag(g_SceneFlags, 0x2E);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            g_GameFlags ^= 0x0E;
            Game_ClearScriptActive();
            *g_ScriptVars = 0;
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;
        case 14:
            break;
    }
}

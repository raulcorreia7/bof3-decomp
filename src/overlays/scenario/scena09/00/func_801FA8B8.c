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
            if (g_UiWindowEffectBusy) {
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
            if (g_UiWindowEffectBusy) {
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

#ifdef NON_MATCHING
NON_MATCHING void func_801FAE0C(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 1;
            Scene_SetupParty(1);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x2D);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 10:
            g_ScenarioState.step = 11;
            Game_RequestAreaChange(AREA_ID_WYNDIA_LOWER, TO_COORD(32), TO_COORD(52), 0x84);
            break;
        case 11:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 0x19) {
                break;
            }
            func_801C1E3C(9);
            SYS_SetFlag(g_SceneFlags, 0x2F);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 15:
            SCENARIO_MESSAGE_WAIT(0xD7, 16);
            break;
        case 16:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            goto clear_script_state;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SYS_ClearFlag(g_Scenario2Flags + 0x20, 0x3E);
            g_ScriptVars[0] = 1;
            Scene_SetupParty(2);
            g_ScenarioState.step = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScenarioState.step = 22;
            Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE, TO_COORD(21), TO_COORD(40), 0x88);
            break;
        case 22:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x30);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 30:
            SCENARIO_MESSAGE_WAIT(0x5A, 16);
            break;
        case 40:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0] = 1;
            Scene_SetupParty(9);
            g_ScenarioState.step = 41;
            break;
        case 41:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x31);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 50:
            Scene_SetupParty(10);
            g_ScenarioState.step = 51;
            break;
        case 51:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x33);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 52:
            SCENARIO_MESSAGE_WAIT(0xA5, 16);
            break;
        case 60:
            g_ScenarioState.step = 61;
            Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE_BASEMENT, TO_COORD(64), TO_COORD_HALF(39), 0x89);
            break;
        case 61:
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 62;
            break;
        case 62:
            if (g_ScriptVars[0] != 0x1E) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x36);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 70:
            if (D_801460FB == 3) {
                break;
            }
            SCENARIO_MESSAGE_WAIT(0x87, 71);
            SYS_ClearFlag(g_SceneEventFlags, 0x45);
            SYS_SetFlag(g_Scenario2Flags + 0x20, 0x3E);
            break;
        case 71:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_ModeSet(UI_MODE_SLOW_FADE_OUT);
            g_ScenarioState.step = 72;
            break;
        case 72:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_ScenarioState.step = 73;
            break;
        case 73:
            SCENARIO_MESSAGE_WAIT(0x88, 74);
            break;
        case 74:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScenarioState.step = 75;
            break;
        case 75:
            g_ScenarioState.step = 76;
            SYS_SetFlag(g_SceneFlags, 0x34);
            Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE, TO_COORD(10), TO_COORD_HALF(45), 0x8B);
            break;
        case 76:
            Area_ScrollStartRoute(3);
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 77;
            break;
        case 77:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SND_XAStartStream(2, 1);
            g_ScenarioState.step = 78;
            break;
        case 78:
            if (SND_XAIsIdle() == 0) {
                break;
            }
            SND_BGMResume(0);
            g_ScenarioState.step = 79;
            break;
        case 79:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]++;
            g_AreaCameraOffsetZ += 0x20;
            if (g_ScriptVars[3] < 0x14) {
                break;
            }
            g_AreaCameraOffsetZ      = 0x280;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 80;
            break;
        case 80:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]++;
            g_AreaCameraOffsetZ -= 0x10;
            if (g_ScriptVars[3] < 0x28) {
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 81;
            break;
        case 81:
            if (g_ScriptVars[0] != 0x1E) {
                break;
            }
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]++;
            g_AreaCameraOffsetZ += 0x80;
            if (g_ScriptVars[3] < 0xA) {
                break;
            }
            g_AreaCameraOffsetZ      = 0x500;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 82;
            break;
        case 82:
            if (g_ScriptVars[0] != 0x1F) {
                break;
            }
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]++;
            g_AreaCameraOffsetZ -= 0x80;
            if (g_ScriptVars[3] < 0xA) {
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 83;
            break;
        case 83:
            if (g_ScriptVars[0] != 0x1F) {
                break;
            }
            g_AreaCameraRefreshCount = 2;
            g_AreaCameraOffsetZ      = 0;
            g_ScenarioState.step     = 90;
            break;
        case 90:
            if (g_ScriptVars[0] != 0x4E) {
                break;
            }
            UI_ModeSet(UI_MODE_SLOW_FADE_OUT);
            g_ScenarioState.step = 91;
            break;
        case 91:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_AreaDrawFlags      = 0;
            g_ScenarioState.step = 92;
            D_80146258 |= 0x88;
            SYS_SetFlag(g_SceneFlags, 0x37);
            Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE_BASEMENT, TO_COORD(64), TO_COORD_HALF(39), 0x8A);
            g_GamePrevSelection = 0x87;
            break;
        case 92:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            UI_ModeSet(UI_MODE_FADE_IN);
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 93;
            break;
        case 93:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0] = 2;
            Area_ScrollStartRoute(6);
            g_ScenarioState.step = 94;
            break;
        case 94:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            SYS_SetFlag(g_Scenario2Flags + 0x20, 0x3E);
            g_ScriptVars[2] = 1;
            SYS_SetFlag(g_SceneFlags, 0x38);
            goto clear_script_state_toggle;
        case 100:
            SCENARIO_MESSAGE_WAIT(0x94, 101);
            break;
        case 101:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_ClearScriptActive();
            goto clear_script_state;
        case 110:
            if (D_801460FB == 3) {
                break;
            }
            SCENARIO_MESSAGE_WAIT(0x9C, 111);
            break;
        case 111:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[2]      = 0;
            g_ScenarioState.step = 112;
            break;
        case 112:
            g_ScenarioState.step = 113;
            Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE_BASEMENT, TO_COORD(4), TO_COORD_HALF(2), 0x8B);
            break;
        case 113:
            g_ScriptVars[0] = 1;
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Area_ScrollStartRoute(7);
            g_ScenarioState.step = 114;
            break;
        case 114:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            g_ScriptVars[2] = 2;
            goto clear_script_state_toggle;
        case 120:
            if (D_801460FB == 3) {
                break;
            }
            g_ScriptVars[2]      = 0;
            g_ScenarioState.step = 121;
            Scene_SetupParty(2);
            break;
        case 121:
            g_ScriptVars[0]      = 1;
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 122;
            break;
        case 122:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScenarioState.step = 123;
            Game_RequestAreaChange(AREA_ID_WYNDIA_BASEMENT_TELEPORTER, TO_COORD(76), TO_COORD_HALF(51), 0x83);
            break;
        case 123:
            Area_ScrollStartRoute(1);
            g_ScenarioState.step = 124;
            break;
        case 124:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScenarioState.step = 125;
            SYS_SetFlag(g_SceneFlags, 0x39);
            Game_RequestAreaChange(AREA_ID_WYNDIA_BASEMENT_TELEPORTER, TO_COORD(74), TO_COORD_HALF(30), 0x84);
            break;
        case 125:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScenarioState.step = 126;
            Game_RequestAreaChange(AREA_ID_WYNDIA_BASEMENT_TELEPORTER, TO_COORD(72), TO_COORD(52), 0x85);
            break;
        case 126:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_ScenarioState.step = 127;
            D_80146258 ^= 0x80;
            SYS_SetFlag(g_SceneEventFlags, 0x40);
            Game_RequestAreaChange(AREA_ID_DURANDAL, TO_COORD(72), TO_COORD(42), 0x82);
            break;
        case 127:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x3A);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 130:
            g_ScenarioState.step = 131;
            Game_RequestAreaChange(AREA_ID_DURANDAL, TO_COORD_HALF(16), TO_COORD(20), 0x83);
            break;
        case 131:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x22);
            Game_ClearScriptActive();
            goto clear_script_state;
        case 140:
            Scene_RunScenario(13);
            g_ScenarioState.step = 141;
            g_AreaDrawFlags      = 0;
            Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD(18), TO_COORD(24), 0x86);
            break;
        case 141:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            UI_ModeSet(UI_MODE_SLOW_FADE_IN);
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_ScenarioState.step = 142;
            break;
        case 142:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0] = 2;
            Area_ScrollStartRoute(3);
            g_ScenarioState.step = 143;
            break;
        case 143:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            UI_ModeSet(UI_MODE_LONG_FADE_OUT);
            g_ScenarioState.step = 144;
            break;
        case 144:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            func_801C16B8();
            g_ScenarioState.step = 145;
            SND_SeqFadeOut(0, 0, 4, 0x1E);
            break;
        case 145:
            SND_XAStartStream(0, 1);
            g_ScenarioState.step = 146;
            break;
        case 146:
            if (SND_XAIsIdle() == 0) {
                break;
            }
            g_ScenarioState.step = 147;
            break;
        case 147:
            SCENARIO_MESSAGE_WAIT(0x37, 148);
            break;
        case 148:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_GameStateIndex     = 6;
            g_ScenarioState.step = 149;
            break;
        case 149:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_ScenarioState.step = 150;
            SYS_SetFlag(g_SceneFlags, 0x23);
            Game_RequestAreaChange(AREA_ID_WYNDIA_WORLD_MAP, TO_COORD(35), TO_COORD(36), 4);
            break;
        case 150:
            SYS_SetFlag(g_SceneEventFlags, 0x33);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            Scene_ClearScriptState(&g_ScenarioState.step);
            break;
    }
    return;

clear_script_state:
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 0;
    return;

clear_script_state_toggle:
    Game_ClearScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 0;
    D_80146258 ^= 8;
}
#else
INCLUDE_ASM(func_801FAE0C);
#endif

MATCH void func_801FBC78(void) {
    u8* step = &g_ScenarioState.step;

    switch (*step) {
        case 0:
            Scene_SetupParty(2);
            *step = 1;
            break;
        case 1:
            if (*g_ScriptVars == 3) {
                SYS_SetFlag(g_SceneFlags, 0x24);
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}

MATCH void func_801FBD0C(void) {
    u8* timer;

    timer = &g_ScenarioState.step;
    if (*timer == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Scene_SetupParty(1);
        g_ScenarioState.state_04 = 0;
        *timer                   = 0;
    }
}

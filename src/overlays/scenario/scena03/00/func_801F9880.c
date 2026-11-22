#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9880(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SCENARIO_MESSAGE_WAIT(MSG_SCENA03_001, 1);
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_ModeSet(1);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Scene_SetupParty(0);
            Area_ScrollStartRoute(0);
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 0x22) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
            g_ScenarioState.timer_06 = 0x2D;
            g_ScenarioState.step     = 3;
            break;
        case 3:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            g_GameFlags &= ~0x80;
            Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE_BASEMENT, TO_COORD(35), TO_COORD(45), FACING_DOWN);
            g_GamePrevSelection  = 0x31;
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            if (g_ScenarioState.timer_06 == 0) {
                UI_ModeSet(1);
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 5;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 5:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x80;
            }
            g_ScenarioState.step = 50;
            break;
        case 50:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            SND_BGMFadeOut(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            SND_BGMPlay(0x55, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 0x18) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 4);
            g_ScenarioState.step = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 0x25) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 3);
            g_ScriptVars[1] = 0;
            Char_RebuildPartyStats();
            Game_ClearScriptActive();
            g_ScenarioState.step = 8;
            break;
        case 8:
            if (g_ScriptVars[1] != 0x15) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 5);
            g_ScenarioState.step = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 0x2B) {
                break;
            }
            g_GameFlags |= 0x80;
            SYS_SetFlag(g_SceneFlags, 6);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 10:
            Game_SetScriptActive();
            Scene_SetupParty(5);
            g_ScenarioState.step = 11;
            break;
        case 11:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x10);
            Game_BattleStartScripted(0x10);
            g_ScenarioState.step = 12;
            break;
        case 12:
            if (g_ScriptVars[0] < 0x14) {
                break;
            }
            if (g_ScriptVars[0] == 0x14) {
                g_AreaCameraSpeed    = 0x20;
                g_ScenarioState.step = 13;
                g_AreaScrollTargetX  = g_Game.members[1].pos.x.fixed;
                g_AreaScrollTargetY  = g_Game.members[1].pos.y.fixed;
            } else {
                UI_ModeSet(0);
                g_ScenarioState.step = 20;
            }
            break;
        case 13:
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_ScriptVars[0]      = 0x15;
            g_ScenarioState.step = 14;
            break;
        case 14:
            if (g_ScriptVars[0] != 0x1D) {
                break;
            }
            SND_BGMPause(g_SndBGMId);
            SND_XAStartStream(3, 1);
            g_ScenarioState.step = 15;
            break;
        case 15:
            if ((u8)SND_XAIsIdle() == 0) {
                break;
            }
            SND_BGMPlay(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step = 16;
            g_ScriptVars[0]++;
            break;
        case 16:
            if (g_ScriptVars[0] != 0x1F) {
                break;
            }
            g_ScriptVars[0]      = 0x58;
            g_ScenarioState.step = 26;
            break;
        case 20:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaScrollTargetX      = TO_COORD(94);
            g_AreaScrollTargetY      = TO_COORD(8);
            g_AreaCameraSpeed        = 0x20;
            g_ScenarioState.timer_06 = 0x78;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 21;
            break;
        case 21:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
            } else {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA03_050, 22);
            }
            break;
        case 22:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_ModeSet(1);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Char_RebuildPartyStats();
            g_ScriptVars[0]      = 0x51;
            g_ScenarioState.step = 23;
            break;
        case 23:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.step = 24;
            break;
        case 24:
            if (g_ScriptVars[0] != 0x55) {
                break;
            }
            SND_BGMPause(g_SndBGMId);
            SND_XAStartStream(3, 1);
            g_ScenarioState.step = 25;
            break;
        case 25:
            if ((u8)SND_XAIsIdle() == 0) {
                break;
            }
            SND_BGMPlay(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step = 26;
            g_ScriptVars[0]++;
            break;
        case 26:
            if (g_ScriptVars[0] != 0x58) {
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            g_GameFlags &= ~0x80;
            break;
    }
}

#include "scena04_00.h"
#include "area/map.h"

/* Runs one step of the scena04 scenario script, picked by g_ScenarioState.step. */
MATCH void func_801F8680(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 1: {
            u16* timer;

            timer = &g_ScenarioState.timer_06;
            if (*timer != 0) {
                *timer = *timer - 1;
                break;
            }
            Scene_SetupParty(0);
            g_ScenarioState.step = 2;
            break;
        }
        case 2:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Area_CellSetPalette(0x57, 0x12);
            SND_SEPlay(0x103);
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            slot                   = Actor_FindFreeSpawned();
            g_ScenarioState.unk_03 = slot;
            if ((s8)slot != -1) {
                g_SpawnedActors[(s8)slot].header.flags           = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[(s8)g_ScenarioState.unk_03].type = 0x29;
            }
            g_ScenarioState.step = 4;
            break;
        case 4:
            if ((g_SpawnedActors[(s8)g_ScenarioState.unk_03].header.flags & ACTOR_FLAG_IN_USE) != 0) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 5;
            break;
        case 5: {
            u16* timer;

            timer = &g_ScenarioState.timer_06;
            if (*timer != 0) {
                *timer = *timer - 1;
                break;
            }
            SND_SEPlay(0x200);
            *timer               = 0x3C;
            g_ScenarioState.step = 6;
            g_ScriptVars[0]++;
            break;
        }
        case 6:
            if (g_ScenarioState.timer_06 != 0) {
                g_AreaCameraHeight += D_801FA21C[g_ScenarioState.timer_06 & 3] * 0x40;
                g_AreaCameraRefreshCount = 2;
                g_ScenarioState.timer_06--;
                break;
            }
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            g_ScriptVars[0]++;
            break;
        case 7:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            SND_StartDecrescendo(0, 1, BGM_CUE_LEVEL_DEFAULT, 0x40);
            SND_XAStartStream(4, 1);
            g_ScenarioState.step = 8;
            break;
        case 8: {
            u16* timer;

            timer = &g_ScenarioState.timer_06;
            if (*timer != 0x80) {
                g_AreaCameraOffsetZ      = *timer * 9;
                g_AreaCameraRefreshCount = 2;
                (*timer)++;
                break;
            }
            SND_SeqStop(0, 1);
            g_ScenarioState.step = 9;
            *timer               = *timer >> 1;
            break;
        }
        case 9: {
            u16* timer;

            timer = &g_ScenarioState.timer_06;
            if (*timer != 0) {
                *timer = *timer - 1;
                break;
            }
            SCENARIO_MESSAGE_WAIT(MSG_SCENA04_013, 10);
            break;
        }
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step = 0xB;
            }
            break;
        case 11:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 0xC;
            break;
        case 12: {
            u16* timer;

            timer = &g_ScenarioState.timer_06;
            if (*timer != 0) {
                *timer = *timer - 1;
                break;
            }
            SCENARIO_MESSAGE_WAIT(MSG_SCENA04_014, 13);
            break;
        }
        case 13:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_ScriptVars[0]++;
            SND_BGMPlay(0x3F, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_AreaDrawFlags          = 0x1F;
            g_AreaCameraOffsetZ      = 0;
            g_AreaCameraRefreshCount = 2;
            UI_ModeSet(UI_MODE_FADE_IN);
            g_ScenarioState.step = 0xE;
            break;
        case 14:
            if (g_ScriptVars[0] == 0x23) {
                UI_ModeSet(UI_MODE_FADE_OUT);
                g_ScenarioState.step = 0xF;
            }
            break;
        case 15:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            func_801C16B8();
            SND_StartDecrescendo(0, 1, BGM_CUE_LEVEL_DEFAULT, 0x10);
            SND_XAStartStream(0, 1);
            g_AreaScrollTargetX = TO_COORD(0xAC);
            g_AreaDrawFlags     = 0;
            g_AreaScrollTargetY = TO_COORD(0x21);
            Area_InitMapRenderer();
            g_ScenarioState.step = 0x10;
            break;
        case 16:
            if (SND_XAIsIdle() == 0) {
                break;
            }
            SND_SeqStop(0, 1);
            SND_BGMPlay(0x30, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScriptVars[0]++;
            g_AreaDrawFlags = 0x1F;
            UI_ModeSet(UI_MODE_FADE_IN);
            g_ScenarioState.step = 0x11;
            break;
        case 17:
            if (g_ScriptVars[0] != 0x2B) {
                break;
            }
            g_ScenarioState.timer_06 = 0xA;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 0x12;
            break;
        case 18: {
            u16* timer;

            timer = &g_ScenarioState.timer_06;
            if (*timer != 0) {
                *timer = *timer - 1;
                break;
            }
            g_ScriptVars[0] = 0;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_OUTSIDE, TO_COORD(0x1E), TO_COORD(0x24), FACING_RIGHT);
            g_GamePrevSelection  = 0x54;
            g_GameEntryMode      = 0xFF;
            g_ScenarioState.step = 0x13;
            break;
        }
        case 19:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_ScenarioState.timer_06 = 0xA;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 0x14;
            g_GameFlags |= 0x80;
            break;
        case 20: {
            u16* timer;

            timer = &g_ScenarioState.timer_06;
            if (*timer != 0) {
                *timer = *timer - 1;
                break;
            }
            g_ScriptVars[1] = 0;
            g_ScriptVars[0] = 0;
            SYS_SetFlag(g_SceneFlags, 4);
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_FIRST_FLOOR, TO_COORD(0xAC), TO_COORD(0x21), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
            g_GameEntryMode      = 0xFF;
            g_ScenarioState.step = 0x15;
            break;
        }
        case 21: {
            u8* vars;

            vars = g_ScriptVars;
            if (vars[0] != 5) {
                break;
            }
            vars[0]         = 0;
            g_ScriptVars[1] = 1;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_FIRST_FLOOR, TO_COORD(0x6C), TO_COORD(7), FACING_UP_LEFT);
            g_ScenarioState.step = 0x16;
            break;
        }
        case 22:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_ScriptVars[0] = 0;
            g_ScriptVars[1] = 2;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_FIRST_FLOOR, TO_COORD(0x42), TO_COORD(6), FACING_UP_LEFT);
            g_ScenarioState.step = 0x17;
            break;
        case 23:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_ScriptVars[1] = 0;
            g_ScriptVars[0] = 0;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_FIRST_FLOOR, TO_COORD(0xAC), TO_COORD(0x21), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
            g_ScenarioState.step = 0x18;
            break;
        case 24:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            SND_StartDecrescendo(0, 3, BGM_CUE_LEVEL_DEFAULT, 0x10);
            SND_XAStartStream(3, 1);
            g_ScenarioState.step = 0x19;
            break;
        case 25:
            if (SND_XAIsIdle() == 0) {
                break;
            }
            g_ScenarioState.step = 0x1B;
            g_ScriptVars[0]++;
            break;
        case 26:
            if (!EMI_IsReady()) {
                break;
            }
            g_ScenarioState.step = 0x1B;
            g_ScriptVars[0]++;
            break;
        case 28:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            D_8014865C           = -2;
            D_80148698           = 1;
            g_GameEntryState     = 7;
            g_MenuStep.step      = 0;
            D_80148699           = 0;
            g_ScenarioState.step = 0x1D;
            break;
        case 29:
            if (g_GameEntryState != 2) {
                break;
            }
        case 30:
            SND_BGMPlay(g_SndBGMId, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScriptVars[0] = 0;
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
}

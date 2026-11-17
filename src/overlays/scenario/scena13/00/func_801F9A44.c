#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9A44(void) {
    u8   index;
    u32  angle;
    u32* angle_cell;
    u8*  progress;
    u16* countdown;

    switch (g_ScenarioState.step_05) {
        case 0:
            SND_FadeOutBGM(g_SndBGMId, 0x64, 8);
            SND_PlaySE(0x208);
            SND_PlaySE(0x207);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            func_801F9E70(D_80147B5C & 0xFFF);
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            angle_cell                    = &D_80147B5C;
            angle                         = *angle_cell;
            LOH(g_ScratchPad.cells.bytes) = angle & 0xFFF;
            if (g_InputHeld & 0x2000) {
                angle += 0x10;
                *angle_cell = angle;
                func_801F9E70(angle & 0xFFF);
            } else if (g_InputHeld & 0x8000) {
                angle -= 0x10;
                *angle_cell = angle;
                func_801F9E70(angle & 0xFFF);
            }
            if (g_InputPressed & 0x40) {
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3: {
            u32 turn = D_80147B5C & 0xFFF;

            LOH(g_ScratchPad.cells.bytes) = turn;
            if (turn - 0x4A0 < 0x41) {
                g_ScenarioState.step_05 = 0xA;
            } else {
                g_ScenarioState.step_05 = 5;
            }
            break;
        }
        case 5:
            SND_PlaySE(0x20A);
            SND_PlaySE(0x209);
            SND_PlayBGM(g_SndBGMId, 0x6E, 0x20);
            g_ScenarioState.timer_06 = 0x30;
            g_ScenarioState.step_05  = 6;
            break;
        case 6:
            countdown  = &g_ScenarioState.timer_06;
            *countdown = *countdown - 1;
            if (*countdown != 0) {
                break;
            }
            Game_ClearScriptActive();
            Scene_SetupParty(1);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 10:
            SND_PlaySE(0x20A);
            SND_PlaySE(0x209);
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step_05  = 0xB;
            break;
        case 11:
            countdown  = &g_ScenarioState.timer_06;
            *countdown = *countdown - 1;
            if (*countdown != 0) {
                break;
            }
            Scene_SetupParty(2);
            Area_SetCellPalette(0xA, 8);
            g_ScenarioState.step_05 = 0xC;
            break;
        case 12:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            index = Actor_FindFreeSpawned();
            if (index != GAME_NONE) {
                g_SpawnedActors[index].header.flags = 1;
                g_SpawnedActors[index].type         = 0x7F;
                g_SpawnedActors[index].pos.x.fixed  = 0x98000;
                g_SpawnedActors[index].pos.y.fixed  = 0x68000;
                g_SpawnedActors[index].pos.z.fixed  = TO_COORD(3840);
            }
            g_ScenarioState.timer_06 = 0x28;
            g_ScenarioState.step_05  = 0xD;
            break;
        case 13:
            countdown  = &g_ScenarioState.timer_06;
            *countdown = *countdown - 1;
            if (*countdown != 0) {
                break;
            }
            g_ScriptVars[0]         = 3;
            g_ScenarioState.step_05 = 0xE;
            break;
        case 14:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            SND_StartXAStream(5, 1);
            Message_StartAreaMessage(MSG_005);
            g_GameStateIndex        = 2;
            g_ScenarioState.step_05 = 0xF;
            break;
        case 15:
            if (SND_IsXAIdle() == 0) {
                break;
            }
            if (g_GameStateIndex == 2) {
                break;
            }
            SND_PlayBGM(g_SndBGMId, 0x6E, 0x20);
            progress                = &g_ScriptVars[0];
            g_ScenarioState.step_05 = 0x10;
            *progress               = *progress + 1;
            break;
        case 16:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x10);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
}

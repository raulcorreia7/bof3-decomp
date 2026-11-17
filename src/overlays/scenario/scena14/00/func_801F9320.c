#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9320(void) {
    u16*          timer;
    u8            slot;
    SpawnedActor* actor;

    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            if ((u8)Scene_SpawnActor(0x13, -0x318, g_AreaCameraAngle.vy, 0x150, 0x70, 0)) {
                g_ScenarioState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            if ((u8)Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x200, 0x40, 0)) {
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 5:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            func_801C601C(1);
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0xE);
            g_ScenarioState.timer_06 = 0x78;
            g_ScenarioState.step_05  = 7;
            break;
        case 7:
            g_ScenarioState.timer_06--;
            if (g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_ScriptVars[0]         = 2;
            g_ScenarioState.step_05 = 2;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x1C) {
                break;
            }
            func_801BFE34(0xB8000, 0x728000, 0x25);
            g_ScenarioState.step_05 = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] != 0x1E) {
                break;
            }
            g_Game.members[2].unk_48 = 1;
            g_Game.members[1].unk_48 = 1;
            g_Game.members[0].unk_48 = 1;
            g_ScenarioState.timer_06 = 0x10;
            g_ScenarioState.step_05  = 0xC;
            break;
        case 12:
            timer = &g_ScenarioState.timer_06;
            (*timer)--;
            if (*timer != 0) {
                g_AreaCameraRefreshCount = 2;
                g_AreaCameraOffsetZ += 0x58;
            } else {
                slot = Actor_FindFreeSpawned();
                if (slot != GAME_NONE) {
                    actor               = &g_SpawnedActors[slot];
                    actor->header.flags = 1;
                    actor->type         = 0x8E;
                }
                *timer                  = 0x64;
                g_ScenarioState.step_05 = 0xD;
            }
            func_801F8800(4);
            break;
        case 13:
            g_ScenarioState.timer_06--;
            if (g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.timer_06 = 0x10;
                g_ScenarioState.step_05  = 0xE;
                g_ScriptVars[0]++;
            }
            func_801F8800(4);
            break;
        case 14:
            g_ScenarioState.timer_06--;
            if (g_ScenarioState.timer_06 != 0) {
                g_AreaCameraRefreshCount = 2;
                g_AreaCameraOffsetZ -= 0x58;
            } else {
                func_801C7A54(0x32);
                g_ScenarioState.step_05 = 0xF;
            }
            break;
        case 16:
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            g_GameFlags &= 0xFFF7;
            SYS_SetFlag(g_SceneFlags, 0xF);
            goto clear_step;
        case 20:
            SCENARIO_MESSAGE_WAIT(MSG_028, 0x15);
            break;
        case 21:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            goto clear_script;
        case 30:
            g_ScriptVars[0] = 0;
            Scene_SetupParty(3);
            g_ScenarioState.step_05 = 0x1F;
            break;
        case 31:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SND_PauseBGM(g_SndBGMId);
            SND_StartXAStream(2, 1);
            Item_VitalAdd(VITAL_ITEM_CARD_KEY_B);
            SCENARIO_MESSAGE_WAIT(MSG_029, 0x20);
            break;
        case 32:
            if (SND_IsXAIdle() == 0) {
                break;
            }
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SND_ResumeBGM(g_SndBGMId);
            g_ScenarioState.step_05 = 0x21;
            g_ScriptVars[0]++;
            break;
        case 2:
        case 33:
            if (g_ScriptVars[0] != 0) {
                break;
            }
        clear_script:
            Game_ClearScriptActive();
        clear_step:
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
}

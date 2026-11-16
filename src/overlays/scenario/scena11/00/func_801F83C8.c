#define GAME_SCRATCH_BASE_SCALAR

#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#define g_TaskMember ((PartyMember*)g_Task)

MATCH void func_801F83C8(void) {
    u8           index;
    PartyMember* work;

    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex != 2) {
                g_ScriptVars[0] = 1;
                Scene_SetupParty(1);
                g_SceneState.step_05 = 1;
            }
            break;
        case 1: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 3) {
                break;
            }
            *progress = 0;
            SND_FadeOutSequence(0, 0, 4, 0x1E);
            SYS_SetFlag(g_SceneFlags, 7);
            g_SceneState.step_05 = 2;
            Game_RequestAreaChange(0x44, 0x300000, 0x198000, 0x82);
            g_GamePrevSelection = 0x7D;
            break;
        }
        case 2:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_SceneState.step_05 = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_SceneState.step_05 = 4;
            break;
        case 4:
            if (g_ScriptVars[0] == 3) {
                Scene_SetupParty(3);
                g_SceneState.step_05 = 2;
            } else if (g_ScriptVars[0] == 0x14) {
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_SceneState.step_05 = 6;
            break;
        case 6: {
            index           = Actor_FindFreeSpawned();
            g_ScratchPad[0] = index;
            if (index != 0xFF) {
                g_SpawnedActors[index].header.flags   = 1;
                g_SpawnedActors[g_ScratchPad[0]].type = 0x8C;
            }
            index           = Actor_FindFreeSpawned();
            g_ScratchPad[0] = index;
            if (index != 0xFF) {
                g_SpawnedActors[index].header.flags   = 1;
                g_SpawnedActors[g_ScratchPad[0]].type = 0x8B;
            }
            g_GameState = &g_Game.members[0];
            TASK_SET(&g_Game.members[0]);
            g_SceneState.step_05 = 7;
            D_80145FA8 |= 0x40;
            break;
        }
        case 8:
            g_GameState = &g_Game.members[0];
            TASK_SET(&g_Game.members[0]);
            D_80145FA8 &= 0xBF;
            SND_PlayCue(0x201);
            SND_FadeOutSequence(0, 1, 4, 0x1E);
            g_SceneState.step_05 = 9;
            break;
        case 9:
            TASK_SET(&g_Game.members[0]);
            g_Task->param.actor_slot = Actor_FindFreeSpawned();
            if (g_Task->param.actor_slot != 0xFF) {
                g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
                g_SpawnedActors[g_Task->param.actor_slot].type         = 6;
                g_SpawnedActors[g_Task->param.actor_slot].unk_06       = 3;
                g_SpawnedActors[g_Task->param.actor_slot].scene_step   = 0;
                g_SpawnedActors[g_Task->param.actor_slot].selection    = 0x3A;
                work                                                   = g_TaskMember;
                g_SpawnedActors[g_Task->param.actor_slot].unk_2E       = work->unk_2E.half;
                g_SpawnedActors[g_Task->param.actor_slot].unk_30       = work->unk_30.half;
                g_SceneState.step_05                                   = 0xA;
            }
            break;
        case 10:
            SND_StartXAStream(6, 1);
            g_SceneState.step_05 = 0xB;
            break;
        case 11:
            if ((SND_IsXAIdle() & 0xFF) == 0) {
                break;
            }
            Message_StartAreaMessage(0x28);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 0xC;
            break;
        case 12:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_SceneState.step_05 = 0xD;
            Game_RequestAreaChange(0x44, 0x2E8000, 0x178000, 0x84);
            g_GamePrevSelection = 0x7C;
            break;
        case 0xD:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 0xF:
            g_GameState = &g_Game.members[0];
            TASK_SET(&g_Game.members[0]);
            D_80145FA8 &= 0xBF;
            SND_FadeOutSequence(0, 1, 4, 0x1E);
            Scene_SetupParty(5);
            g_SceneState.step_05 = 0x10;
            break;
        case 0x10:
            SND_StartXAStream(5, 1);
            g_SceneState.step_05 = 0x11;
            break;
        case 0x11:
            if ((SND_IsXAIdle() & 0xFF) == 0) {
                break;
            }
            g_ScriptVars[0]      = 2;
            g_SceneState.step_05 = 0x12;
            break;
        case 0x12: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 5) {
                break;
            }
            *progress            = 0;
            g_SceneState.step_05 = 0x13;
            SYS_SetFlag(g_SceneFlags, 8);
            Game_RequestAreaChange(0x44, 0x2E8000, 0x178000, 0x86);
            g_GamePrevSelection = 0x7C;
            break;
        }
        case 0x13:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            if ((Item_Add(0, 0x24, 4, 0) & 0xFF) == 0) {
                strncpy((char*)g_TextVariables[0], (char*)Item_GetRecord(0, 0x24), 12);
                D_801490E4[0] = 0;
                Message_StartAreaMessage(0x33);
                g_GameStateIndex     = 2;
                g_SceneState.step_05 = 0x14;
            } else {
                Message_StartAreaMessage(0x32);
                g_GameStateIndex = 2;
                SND_PlayCue(0x106);
                g_SceneState.step_05 = 0x14;
            }
            break;
        case 0x14:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScriptVars[0]      = 2;
            g_SceneState.step_05 = 0x16;
            break;
        case 0x16:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 0x28: {
            u8* progress;

            if (g_GameStateIndex == 2) {
                break;
            }
            progress = &g_ScriptVars[0];
            if (*progress == 0xFF) {
                Game_ClearScriptActive();
                *progress             = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            } else {
                *progress = 0;
                Scene_SetupParty(9);
                g_SceneState.step_05 = 0x29;
            }
            break;
        }
        case 0x29: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_SceneState.step_05 = 0x2A;
            SND_FadeOutSequence(0, 0, 4, 0x1E);
            Game_RequestAreaChange(0x44, 0x300000, 0x198000, 0x88);
            g_GamePrevSelection = 0x7D;
            break;
        }
        case 0x2A:
            if (g_ScriptVars[0] == 3) {
                Scene_SetupParty(3);
                g_SceneState.step_05 = 2;
            } else if (g_ScriptVars[0] == 0x14) {
                g_SceneState.step_05 = 5;
            }
            break;
    }
}

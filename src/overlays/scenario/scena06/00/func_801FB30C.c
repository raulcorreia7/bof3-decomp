#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Step script: party lines, a field actor for Ryu in the party, then scripted battle 0x1C. */
MATCH void func_801FB30C(void) {
    u8 i;

    switch (g_ScenarioState.step_05) {
        case 0:
            Scene_SetupParty(3);
            Area_ScrollStartRoute(0);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 4) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 2) {
                    UI_MessageStartArea(MSG_SCENA06_018);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 5) {
                    UI_MessageStartArea(MSG_SCENA06_017);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 1) {
                    UI_MessageStartArea(MSG_SCENA06_016);
                }
            }
            g_GameStateIndex        = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_PartyFieldOrder[0] == 0) {
                TASK_SET(&g_Game.members[0]);
                TASK(Actor)->param.actor_slot = Actor_FindFreeSpawned();
                if (TASK(Actor)->param.actor_slot != GAME_NONE) {
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 6;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_06       = 3;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].scene_step   = 0;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].selection    = D_801FE3BC[g_PartyFieldOrder[0]];
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].screen_x     = TASK(Actor)->screen_x;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].screen_y     = TASK(Actor)->screen_y;
                }
            }
            if (g_PartyFieldOrder[1] == 0) {
                TASK_SET(&g_Game.members[1]);
                TASK(Actor)->param.actor_slot = Actor_FindFreeSpawned();
                if (TASK(Actor)->param.actor_slot != GAME_NONE) {
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 6;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_06       = 3;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].scene_step   = 0;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].selection    = D_801FE3BC[g_PartyFieldOrder[1]];
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].screen_x     = TASK(Actor)->screen_x;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].screen_y     = TASK(Actor)->screen_y;
                }
            }
            if (g_PartyFieldOrder[2] == 0) {
                TASK_SET(&g_Game.members[2]);
                TASK(Actor)->param.actor_slot = Actor_FindFreeSpawned();
                if (TASK(Actor)->param.actor_slot != GAME_NONE) {
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = 6;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].unk_06       = 3;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].scene_step   = 0;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].selection    = D_801FE3BC[g_PartyFieldOrder[2]];
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].screen_x     = TASK(Actor)->screen_x;
                    g_SpawnedActors[TASK(Actor)->param.actor_slot].screen_y     = TASK(Actor)->screen_y;
                }
            }
            g_ScenarioState.step_05 = 5;
            g_ScriptVars[0]         = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 10) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 40);
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 10:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            func_801FCB80(0x93);
            g_ScenarioState.step_05 = 11;
            break;
        case 11:
            func_801FBC88();
            break;
        case 12:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Scene_SetupParty(4);
            g_ScenarioState.step_05 = 13;
            break;
        case 13:
            if (g_ScriptVars[0] != 15) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 41);
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
        case 20:
            D_80146258 |= 8;
            SND_SeqStop(0, 0);
            Scene_SetupParty(5);
            g_ScenarioState.step_05 = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 0x15) {
                break;
            }
            Area_ScrollStartRoute(1);
            g_ScenarioState.step_05 = 22;
            break;
        case 22:
            if (g_ScriptVars[0] != 0x1A) {
                break;
            }
            func_801BFE34(0x2E0000, 0x60000, 0x1C);
            g_ScenarioState.step_05 = 23;
            break;
        case 23:
            if (g_ScriptVars[0] != 0x1C) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 5) {
                    UI_MessageStartArea(MSG_SCENA06_025);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 1) {
                    UI_MessageStartArea(MSG_SCENA06_024);
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_PartyFieldOrder[i] == 2) {
                    UI_MessageStartArea(MSG_SCENA06_023);
                }
            }
            g_GameStateIndex        = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step_05 = 30;
            break;
        case 30:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_BattleStartScripted(0x1C);
            g_ScenarioState.step_05 = 35;
            break;
        case 35:
            if (g_ScriptVars[0] != 30) {
                break;
            }
            D_80146258 ^= 8;
            SYS_SetFlag(g_SceneFlags, 42);
            g_ScriptVars[1] = 0;
            g_ScriptVars[2] = 0;
            g_ScriptVars[3] = 0;
            Game_ClearScriptActive();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}

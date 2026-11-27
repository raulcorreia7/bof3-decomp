#include "scena08_00.h"
#include "area/map.h"
#include "engine/area/collision/collision.h"
#include "engine/sound/sound.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Scene 08 step script: the balcony scene, the party transition and the return to the world map. */
MATCH void func_801FC45C(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (!WINDOW_EFFECT_BUSY()) {
                Game_RequestAreaChange(0xB, 0x138000, 0x238000, 0x84);
                g_GameRequestType    = 0xFF;
                g_GameEntryMode      = 0xFF;
                g_GamePrevSelection  = 0xFF;
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (!WINDOW_EFFECT_BUSY()) {
                UI_MessageStartArea(0x27);
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (g_GameStateIndex != 2) {
                g_AreaDrawFlags = 0x1F;
                SND_BGMStart(0xC, 100, 0x20);
                UI_ModeSet(1);
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (!WINDOW_EFFECT_BUSY()) {
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 2) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = -0x44C;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x124;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x40;
                }
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 5) {
                UI_ModeSet(6);
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_GameStateIndex != 2) {
                SYS_SetFlag(g_SceneFlags, 0xC);
                Game_RequestAreaChange(0xC, D_801FEA74, D_801FEA78, D_801FEA70);
                g_GameEntryMode      = 0xFF;
                g_GameRequestType    = 0xFF;
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            if (!WINDOW_EFFECT_BUSY() && g_GameStateIndex != 5) {
                UI_ModeSet(1);
                g_AreaDrawFlags = 0x1F;
                g_ScriptVars[0] = 0;
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 10:
            if (g_ScenarioState.timer_06-- == 0) {
                Game_ClearScriptActive();
                Scene_SetupParty(0);
                g_ScenarioState.step = 11;
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 2) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x2B0;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x20;
                    g_ScenarioState.step                       = 12;
                    g_ScenarioState.timer_06                   = 0x20;
                    SND_StartDecrescendo(g_SelectionSepSlots[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4], 100, 0x20);
                }
            }
            break;
        case 12:
            if (g_ScenarioState.timer_06-- == 0) {
                SND_BGMFadeOut(g_SndBGMId, 100, 0x20);
                SND_SEPlay(0x201);
                g_ScenarioState.step = 13;
                g_ScriptVars[0]++;
            }
            break;
        case 13:
            if (g_ScriptVars[0] == 6) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x20;
                    g_ScenarioState.step                       = 14;
                }
            }
            break;
        case 14:
            if (!(g_SpawnedActors[D_801FEA6C].header.flags & 1)) {
                D_80146258 |= 0x20;
                g_ScriptVars[0] = g_ScriptVars[0] + 1;
                D_801FEA7C[0]   = g_PartyBattleOrder[0];
                D_801FEA7C[1]   = g_PartyBattleOrder[1];
                func_801C1E3C(0);
                func_801FD07C();
                g_ScenarioState.step = 15;
            }
            break;
        case 20:
            Scene_SetupParty(1);
            g_ScenarioState.step = 21;
            break;
        case 21:
            if (g_ScriptVars[0] == 10) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x13A;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x40;
                    g_ScenarioState.step                       = 22;
                }
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 0x12) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x360;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x20;
                    Area_ScrollStartRoute(0);
                    g_ScenarioState.step = 23;
                    D_80146258 |= GAME_FLAG_SCROLL_LOCK;
                }
            }
            break;
        case 23:
            if (g_ScriptVars[0] == 0x16) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != 0xFF) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x20;
                    g_ScenarioState.step                       = 24;
                }
            }
            break;
        case 24:
            if (g_ScriptVars[0] == 0x1A) {
                Game_ClearScriptActive();
                SND_BGMFadeOut(g_SndBGMId, 100, 8);
                SYS_SetFlag(g_SceneFlags, 0xD);
                g_ScenarioState.timer_06 = 0x3C;
                g_ScenarioState.step     = 25;
            }
            break;
        case 25:
            if (g_ScenarioState.timer_06-- == 0) {
                SND_BGMStart(g_GamePrevSelection, 100, 8);
                g_ScenarioState.step = 26;
            }
            break;
        case 26:
            if (g_UIMessageRequest == 0xE && g_GameStateIndex == 2) {
                D_801FEA70 = g_ScriptWorkRecord - g_Actors;
                D_801FEA74 = g_ScriptWorkRecord->pos.x.fixed;
                D_801FEA78 = g_ScriptWorkRecord->pos.y.fixed;
                Scene_SetupParty(2);
                g_ScenarioState.step = 27;
            }
            break;
        case 27:
            if (g_ScriptVars[0] == 0) {
                SYS_SetFlag(g_SceneFlags, 0xE);
                D_80146258 &= ~0x20;
                g_Actors[D_801FEA70].header.flags = 0;
                Scene_RunScenario(2);
                g_PartyBattleOrder[0]                = D_801FEA7C[0];
                g_PartyBattleOrder[1]                = D_801FEA7C[1];
                g_Game.members[1].pos.x.fixed        = D_801FEA74;
                g_Game.members[1].pos.y.fixed        = D_801FEA78;
                g_Game.members[1].pos.z.part.integer = Area_HeightSample(D_801FEA74, D_801FEA78);
                g_ScenarioState.state_04             = 0;
                g_ScenarioState.step                 = 0;
            }
            break;
    }
}

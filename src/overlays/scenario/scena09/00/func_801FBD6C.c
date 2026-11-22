#include "scena09_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBD6C(void) {
    switch (g_ScenarioState.step) {
        case 0:
            Scene_SetupParty(2);
            g_ScriptVars[0]      = 0x20;
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 0x25) {
                break;
            }
            D_801FE554 = Actor_FindFreeSpawned();
            if (D_801FE554 != GAME_NONE) {
                g_SpawnedActors[D_801FE554].header.flags   = 1;
                g_SpawnedActors[D_801FE554].type           = 0x13;
                g_SpawnedActors[D_801FE554].camera_angle.x = -0x3C8;
                g_SpawnedActors[D_801FE554].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE554].camera_angle.z = 0xF8;
                g_SpawnedActors[D_801FE554].layer          = 0x30;
                g_ScenarioState.step                       = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] != 0x26) {
                break;
            }
            D_801FE554 = Actor_FindFreeSpawned();
            if (D_801FE554 != GAME_NONE) {
                g_SpawnedActors[D_801FE554].header.flags = 1;
                g_SpawnedActors[D_801FE554].type         = 0x2B;
                g_SpawnedActors[D_801FE554].pos.x.fixed  = TO_COORD_HALF(35);
                g_SpawnedActors[D_801FE554].pos.y.fixed  = TO_COORD_HALF(31);
                g_SpawnedActors[D_801FE554].pos.z.fixed  = TO_COORD(Area_HeightSample(g_SpawnedActors[D_801FE554].pos.x.fixed, TO_COORD_HALF(31)));
            }
            g_ScenarioState.timer_06 = 0x5F;
            g_ScenarioState.step     = 3;
            break;
        case 3:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            g_ScenarioState.step = 4;
            g_ScriptVars[0]++;
            break;
        case 4:
            if (g_ScriptVars[0] != 0x28) {
                break;
            }
            D_801FE554 = Actor_FindFreeSpawned();
            if (D_801FE554 != GAME_NONE) {
                g_SpawnedActors[D_801FE554].header.flags   = 1;
                g_SpawnedActors[D_801FE554].type           = 0x13;
                g_SpawnedActors[D_801FE554].camera_angle.x = g_AreaCameraAngle.vx;
                g_SpawnedActors[D_801FE554].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE554].camera_angle.z = -0x144;
                g_SpawnedActors[D_801FE554].layer          = 0x28;
                g_ScenarioState.step                       = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] != 0x29) {
                break;
            }
            g_ScenarioState.timer_06 = 0x78;
            g_ScenarioState.step     = 6;
            break;
        case 6:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            D_801FE554 = Actor_FindFreeSpawned();
            if (D_801FE554 != GAME_NONE) {
                g_SpawnedActors[D_801FE554].header.flags   = 1;
                g_SpawnedActors[D_801FE554].type           = 0x13;
                g_SpawnedActors[D_801FE554].camera_angle.x = g_AreaCameraAngle.vx;
                g_SpawnedActors[D_801FE554].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE554].camera_angle.z = 0x200;
                g_SpawnedActors[D_801FE554].layer          = 0x20;
                g_ScenarioState.step                       = 7;
            }
            break;
        case 7:
            if (g_SpawnedActors[D_801FE554].header.flags & 1) {
                break;
            }
            D_801FE554 = Actor_FindFreeSpawned();
            if (D_801FE554 != GAME_NONE) {
                g_SpawnedActors[D_801FE554].header.flags   = 1;
                g_SpawnedActors[D_801FE554].type           = 0x13;
                g_SpawnedActors[D_801FE554].camera_angle.x = -0x2AA;
                g_SpawnedActors[D_801FE554].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE554].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[D_801FE554].layer          = 0x7C;
                g_ScenarioState.step                       = 8;
                g_ScriptVars[0]++;
            }
            break;
        case 8:
            if (g_ScriptVars[0] != 0x32) {
                break;
            }
            g_ScenarioState.timer_06 = 0x5A;
            g_ScenarioState.step     = 9;
            break;
        case 9:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            g_ScenarioState.step = 10;
            g_ScriptVars[0]++;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x35) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 11;
            break;
        case 11:
            if (!TIMER_EXPIRED(g_ScenarioState.timer_06)) {
                break;
            }
            g_ScenarioState.step = 12;
            g_ScriptVars[0]++;
            break;
        case 12:
            if (g_ScriptVars[0] != 0x37) {
                break;
            }
            g_ScenarioState.step = 13;
            break;
        case 13:
            if (g_ScriptVars[0] != 0x3B) {
                break;
            }
            g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
            g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
            Area_InitMapRenderer();
            g_ScenarioState.step = 14;
            break;
        case 14:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x20);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 30:
            Game_ClearScriptActive();
            Scene_SetupParty(3);
            g_ScriptVars[0] = 0x20;
            Scene_RequestChapterAdvance();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 35:
            Game_ClearScriptActive();
            Scene_SetupParty(4);
            g_ScriptVars[0]          = 0x20;
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
    }
}

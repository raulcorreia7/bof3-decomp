#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Runs the scene script one step per frame, keyed on g_ScenarioState.step. */
MATCH void func_801FBCA4(void) {
    SpawnedActor* actor;
    u8            slot;

    switch (g_ScenarioState.step) {
        case 0:
            SND_StartDecrescendo(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence, 100, 0x20);
            g_ScenarioState.timer_06 = 0x20;
            g_ScenarioState.step     = 1;
            break;
        case 1:
            if (g_ScenarioState.timer_06-- == 0) {
                SND_BGMFadeOut(g_SndBGMId, 100, 0x20);
                g_ScriptVars[0] = 0;
                func_801BE1B0(0);
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 1) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = -0x318;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x1E;
                }
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (!(g_SpawnedActors[D_801FEA6C].header.flags & 1)) {
                slot                        = Actor_FindFreeSpawned();
                g_ScratchPad.cells.bytes[0] = slot;
                if (slot != GAME_NONE) {
                    actor               = &g_SpawnedActors[slot];
                    actor->header.flags = 1;
                    actor->type         = 0x5F;
                    actor->header.mode  = 0;
                }
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x1C;
                    g_SpawnedActors[D_801FEA6C].layer          = 0xB4;
                }
                g_ScenarioState.step = 4;
                g_ScriptVars[0]++;
            }
            break;
        case 4:
            if (!(g_SpawnedActors[D_801FEA6C].header.flags & 1)) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags         = 1;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = 0;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x5A;
                }
                g_ScriptVars[0]++;
                func_801BFE34(TO_COORD(0x43), TO_COORD(0x38), 0x21);
                func_801BE1B0(1);
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (!(g_SpawnedActors[D_801FEA6C].header.flags & 1)) {
                g_ScenarioState.step = 6;
                g_ScriptVars[0]++;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 5) {
                func_801C7A54(0x21);
                g_ScenarioState.step = 7;
            }
            break;
        case 8:
            g_ScriptVars[0] = 0;
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 8);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            D_80146258 &= ~GAME_FLAG_SCROLL_LOCK;
            break;
    }
}

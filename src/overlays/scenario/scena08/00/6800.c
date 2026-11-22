#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FD400(void) {
    u8 slot;

    switch (g_ScenarioState.step_05) {
        case 0:
            Game_ClearScriptActive();
            Scene_SetupParty(1);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
        case 10:
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -748;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 182;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x20;
                g_ScenarioState.step_05                                     = 11;
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 0x6) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags         = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = -682;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = ANGLE_45;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x20;
                    g_ScenarioState.step_05                    = 12;
                }
            }
            break;
        case 12:
            if ((g_SpawnedActors[D_801FEA6C].header.flags & ACTOR_FLAG_IN_USE) == 0) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x14);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
    }
}

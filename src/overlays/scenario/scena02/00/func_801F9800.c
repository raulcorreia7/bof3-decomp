#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9800(void) {
    u8 slot;

    switch (g_SceneState.step_05) {
        case 0:
            Scene_SetupParty(6);
            Area_StartScrollRoute(2);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x2B) {
                func_801BFE34(TO_COORD(0x10), TO_COORD(7), 0xA);
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2BA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x260;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
                g_SceneState.step_05                                        = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x2F) {
                Battle_StartScripted(0xA);
                g_SceneState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x30) {
                Scene_SetupParty(0x16);
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x14;
                g_SceneState.step_05                                        = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x31) {
                SYS_SetFlag(g_SceneFlags, 0x12);
                SYS_SetFlag(g_SceneFlags, 0x13);
                Game_ClearScriptActive();
                D_80146865            = 0;
                D_80146866            = 0;
                D_80146867            = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}

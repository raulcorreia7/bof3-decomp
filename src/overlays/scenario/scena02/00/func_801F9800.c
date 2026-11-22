#include "scena02_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9800(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            Scene_SetupParty(6);
            Area_ScrollStartRoute(2);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x2B) {
                func_801BFE34(TO_COORD(0x10), TO_COORD(7), 0xA);
                g_ScenarioState.step = 2;
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
                g_ScenarioState.step                                        = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x2F) {
                Game_BattleStartScripted(0xA);
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x30) {
                Scene_SetupParty(0x16);
                g_ScenarioState.step = 5;
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
                g_ScenarioState.step                                        = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x31) {
                SYS_SetFlag(g_SceneFlags, 0x12);
                SYS_SetFlag(g_SceneFlags, 0x13);
                Game_ClearScriptActive();
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}

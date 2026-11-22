#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8C78(void) {
    u8  slot;
    u8* actor_slot_address;

    switch (g_ScenarioState.step_05) {
        case 0:
            if (!SYS_TestFlag(g_SceneFlags, 0x35)) {
                SND_SeqStop(0, 1);
            }
            SND_SeqStop(0, 0);
            Scene_SetupParty(0x18);
            Area_StartScrollRoute(5);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x2C6;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x10;
                g_ScenarioState.step_05                                     = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] != 0xA2) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 0x1FE;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x10;
                g_ScenarioState.step_05                                     = 3;
                g_ScriptVars[3]                                             = g_ScratchPad.cells.bytes[0];
            }
            break;
        case 3:
            actor_slot_address = &g_ScriptVars[3];
            if (g_SpawnedActors[*actor_slot_address].header.flags != 0) {
                break;
            }
            *actor_slot_address = 0;
            Scene_SetupParty(10);
            g_ScenarioState.step_05 = 4;
            break;
        case 4:
            if (g_ScriptVars[0] != 0x63) {
                break;
            }
            D_80146258 |= 8;
            SND_BGMPlay(0x20, 0x64, 8);
            g_ScenarioState.step_05 = 5;
            D_80146258 |= 0x80;
            break;
        case 5:
            if (g_ScriptVars[0] != 0x71) {
                break;
            }
            Area_StartScrollRoute(1);
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 0x7E) {
                break;
            }
            g_ScriptVars[2] = 0;
            D_80146258 ^= 8;
            func_801C1E3C(0);
            g_ScenarioState.step_05 = 7;
            D_80146258 ^= 0x80;
            Game_RequestAreaChange(0x1B, TO_COORD(0x22), TO_COORD(0x26), 0x80);
            break;
        case 7:
            SYS_SetFlag(g_SceneFlags, 0x3F);
            Game_ClearScriptActive();
            g_ScriptVars[2]          = 1;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}

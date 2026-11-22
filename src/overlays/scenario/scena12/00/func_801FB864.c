#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FB864(void) {
    u8  slot;
    u8* char_slots;

    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScenarioState.step_05 = 1;
            Game_RequestAreaChange(AREA_ID_WYNDIA_HONEY_BALCONY, TO_COORD(113) + COORD_HALF, TO_COORD(9), AREA_ENTRY_MAP_LOADING);
            g_GamePrevSelection = 0xFF;
            break;
        case 1:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0] = 1;
            Area_StartScrollRoute(0);
            g_ScenarioState.step_05 = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x31;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = g_AreaCameraAngle.vx;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 292;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].scene_step     = 0x700;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x5A;
                g_ScenarioState.step_05                                     = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SND_BGMPlay(0x27, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_ScenarioState.step_05 = 5;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            break;
        case 5:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -949;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x1E;
                g_ScenarioState.step_05                                     = 7;
            }
            break;
        case 7:
            SND_SeqStop(0, 2);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
            g_ScenarioState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 0xC) {
                break;
            }
            SND_BGMPlay(0x24, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
            g_ScenarioState.step_05 = 9;
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            break;
        case 9:
            if (g_ScriptVars[0] != 0xD) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -682;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x1E;
                g_ScenarioState.step_05                                     = 10;
            }
            break;
        case 10:
            if (g_ScriptVars[0] != 0xE) {
                break;
            }
            g_ScenarioState.step_05 = 11;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            SYS_SetFlag(g_SceneFlags, 10);
            Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD(35), TO_COORD(41), AREA_ENTRY_MAP_LOADING);
            break;
        case 11:
            Area_StartScrollRoute(0);
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = 0;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 2;
                g_ScenarioState.step_05                                     = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = 1;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -682;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x78;
                g_ScenarioState.step_05                                     = 13;
            }
            break;
        case 13:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            g_ScenarioState.step_05 = 14;
            SYS_SetFlag(g_SceneFlags, 11);
            SYS_SetFlag(g_SceneFlags, 9);
            Item_VitalAdd(VITAL_ITEM_PASSPORT);
            break;
        case 14:
            if (g_ScriptVars[0] != 0x32) {
                break;
            }
            g_ScenarioState.step_05 = 15;
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            /* FAKE: retail reads g_CharSlot as u8[]. */
            char_slots = (u8*)g_CharSlot;
            g_Characters[char_slots[CHAR_ID_PECO]].party_flags |= PARTY_FLAG_JOINED;
            g_Characters[char_slots[CHAR_ID_GARR]].party_flags |= PARTY_FLAG_JOINED;
            Game_RequestAreaChange(AREA_ID_WYNDIA_WORLD_MAP, TO_COORD(34), TO_COORD(42), FACING_RIGHT);
            break;
        case 15:
            Char_RebuildPartyStats();
            Game_ClearScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 0;
            break;
    }
}
#else
INCLUDE_ASM(func_801FB864);
#endif

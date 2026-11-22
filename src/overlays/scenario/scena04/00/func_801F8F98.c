#include "scena04_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Spawns one actor of type 0x13 at the camera angle (angle_x, angle_y, angle_z) on layer_id. */
#define SCENE_SPAWN_AT(angle_x, angle_y, angle_z, layer_id)                       \
    g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();                        \
    if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {                               \
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags   = 1;          \
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;       \
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = (angle_x);  \
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = (angle_y);  \
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = (angle_z);  \
        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = (layer_id); \
    }

/* The scena04 opening: the map flyover, the camera actors and the area change that follows it. */
MATCH void func_801F8F98(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScriptVars[0] = 0;
            Scene_SetupParty(4);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 0xC) {
                break;
            }
            SND_BGMFadeOut(g_SndBGMId, 100, 8);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            g_AreaSceneMode          = 1;
            g_ScenarioState.timer_06 = 0x60;
            g_ScenarioState.step_05  = 3;
            break;
        case 3:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 4;
            break;
        case 4:
            g_AreaScrollTargetX = TO_COORD(78);
            g_AreaScrollTargetY = TO_COORD(40);
            Area_InitMapRenderer();
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step_05  = 5;
            break;
        case 5:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 0x11) {
                break;
            }
            g_AreaDrawFlags         = 0;
            g_ScenarioState.step_05 = 7;
            break;
        case 7:
            g_AreaScrollTargetX = TO_COORD(133);
            g_AreaScrollTargetY = TO_COORD(10);
            Area_InitMapRenderer();
            SND_BGMRequest(0x41);
            g_ScenarioState.step_05 = 30;
            break;
        case 30:
            if (!EMI_IsReady()) {
                break;
            }
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step_05  = 8;
            break;
        case 8:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_AreaCameraAngle.vx = -0x35A;
            g_AreaCameraAngle.vz = 0x74;
            g_AreaCameraOffsetZ  = 0x400;
            Area_ScrollAdvance(0x100);
            g_ScriptVars[0]++;
            SND_BGMStart(0x41, 100, 8);
            Scene_SetupParty(5);
            SCENE_SPAWN_AT(g_AreaCameraAngle.vx, g_AreaCameraAngle.vy, 0x192, 0x3C);
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step_05  = 9;
            break;
        case 9:
            if (--g_ScenarioState.timer_06 != 0) {
                g_AreaCameraOffsetZ -= 0x22;
                if (g_AreaCameraOffsetZ < 0) {
                    g_AreaCameraOffsetZ = 0;
                }
                break;
            }
            g_AreaCameraOffsetZ      = 0;
            g_ScenarioState.timer_06 = 0x1E;
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 10;
            break;
        case 10:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SCENE_SPAWN_AT(-0x2D6, g_AreaCameraAngle.vy, 0x2B0, 0x3C);
            g_ScenarioState.timer_06 = 0xF;
            g_ScenarioState.step_05  = 11;
            break;
        case 11:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScenarioState.timer_06 = 0xF;
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 12;
            break;
        case 12:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScriptVars[0]++;
            g_ScenarioState.step_05 = 13;
            break;
        case 13:
            if (g_ScenarioState.timer_06 != 0) {
                g_ScenarioState.timer_06--;
                break;
            }
            Area_ScrollAdvance(0x180);
            g_ScenarioState.step_05 = 14;
            break;
        case 14:
            if (g_ScriptVars[0] != 0x22) {
                break;
            }
            g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
            if (g_ScratchPad.cells.bytes[0] == GAME_NONE) {
                break;
            }
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
            g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x2C;
            g_ScenarioState.step_05                                   = 15;
            break;
        case 15:
            if (g_ScriptVars[0] != 0x23) {
                break;
            }
            SCENE_SPAWN_AT(-0x3B2, g_AreaCameraAngle.vy, g_AreaCameraAngle.vz, 0x1E);
            g_ScenarioState.timer_06 = 0xA0;
            g_ScenarioState.step_05  = 16;
            break;
        case 16:
            if (g_ScenarioState.timer_06 != 0) {
                g_AreaCameraOffsetZ += 9;
                if (g_AreaCameraOffsetZ > 0x400) {
                    g_AreaCameraOffsetZ = 0x400;
                }
                g_ScenarioState.timer_06--;
                break;
            }
            g_GameFlags |= 0x80;
            Game_RequestAreaChange(AREA_ID_MOMO_TOWER_WORLD_MAP, TO_COORD(46), TO_COORD(33), 1);
            g_GameRequestType = 0xFF;
            SYS_SetFlag(g_SceneFlags, 7);
            g_ScenarioState.step_05 = 17;
            break;
        case 17:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            SND_StartDecrescendo(0, 1, 0x6E, 0x10);
            g_ScenarioState.timer_06 = 0x1F;
            g_ScenarioState.step_05  = 18;
            break;
        case 18:
            if (--g_ScenarioState.timer_06 != 0xC) {
                break;
            }
            SCENE_SPAWN_AT(-0x58, g_AreaCameraAngle.vy, g_AreaCameraAngle.vz, 0xA);
            g_ScenarioState.step_05 = 19;
            break;
        case 19:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SCENE_SPAWN_AT(g_AreaCameraAngle.vx, g_AreaCameraAngle.vy, -0x262, 0x20);
            g_ScenarioState.step_05 = 20;
            break;
        case 20:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step_05  = 21;
            break;
        case 21:
            if (--g_ScenarioState.timer_06 >= 0x13) {
                func_801F9CFC();
            }
            if (g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_GameFlags &= ~0x80;
            Game_RequestAreaChange(AREA_ID_ROCKET_LANDING, TO_COORD(14), TO_COORD(16), 0x80);
            g_GameEntryMode         = 0;
            g_ScenarioState.step_05 = 22;
            break;
        case 22:
            if (g_ScriptVars[0] != 0x11) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            SYS_SetFlag(g_SceneFlags, 0xC);
            func_801A78F8();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
    if (g_ScenarioState.step_05 >= 2 && g_ScenarioState.step_05 <= 12) {
        func_801F9CFC();
    }
}

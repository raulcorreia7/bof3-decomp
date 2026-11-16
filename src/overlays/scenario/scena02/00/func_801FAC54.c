#include "scena02_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FAC54(void) {
    u8 slot;

    switch (g_SceneState.step_05) {
        case 10:
            g_SceneState.step_05 = 0xB;
            SYS_SetFlag(g_SceneFlags, 0x1D);
            Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE_BALIO_SUNDER, TO_COORD(0x20), TO_COORD(0x11), AREA_ENTRY_MAP_LOADING);
            break;
        case 11:
            UI_SetMode(5);
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 0xC;
            break;
        case 12:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScriptVars[0] = 1;
            func_801C601C(0);
            slot                      = Actor_FindFreeSpawned();
            D_1F800000.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                        = 1;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.x = -0x4D0;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.z = 0x2B0;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].layer          = 0xB4;
                g_SceneState.step_05                                      = 0xD;
            }
            break;
        case 13:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            slot                      = Actor_FindFreeSpawned();
            D_1F800000.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                        = 1;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.x = -0x2AA;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.z = 0x200;
                g_SpawnedActors[D_1F800000.cells.bytes[0]].layer          = 0x40;
                g_SceneState.step_05                                      = 0xE;
            }
            break;
        case 14:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            D_80146258 |= 8;
            func_801BE1B0(1);
            g_SceneState.step_05 = 0xF;
            break;
        case 15:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SND_StopSequence(0, 0);
            SND_PlayBGM(0xD, 0x64, 8);
            g_SceneState.step_05 = 0x10;
            g_ScriptVars[0]      = 0x1E;
            Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_HOUSE_BALIO_SUNDER, TO_COORD(0x22), TO_COORD(0x11), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
            g_GamePrevSelection = 0xD;
            break;
        case 16:
            if (g_ScriptVars[0] != 0x27) {
                break;
            }
            func_801BFE34(TO_COORD(0x1E), TO_COORD(0x11), 0xD);
            func_801C7A54(0xD);
            g_SceneState.step_05 = 0x11;
            break;
        case 17:
            if (g_ScriptVars[0] != 0x3C) {
                break;
            }
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            D_80146866            = 0;
            SYS_SetFlag(g_SceneFlags, 0x1E);
            Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_BUNYAN, TO_COORD(0x4F), TO_COORD(0x1A), AREA_ENTRY_MAP_LOADING);
            g_GamePrevSelection = 0xFF;
            break;
        case 18:
        case 19:
        case 20:
            break;
    }
}

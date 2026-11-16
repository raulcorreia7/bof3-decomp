#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8CE4(void) {
    u8* mode;
    u8  slot;

    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVars[0] = 0;
            SYS_SetFlag(g_SceneFlags, 0x10);
            Game_RequestAreaChange(AREA_ID_CAER_XHAN_LIFT_AREA, TO_COORD(24), TO_COORD_HALF(38), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            if ((u8)Scene_SpawnActor(0x13, -0x344, g_AreaCameraAngle.vy, 0x284, 0x98, 0)) {
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            if ((u8)Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x200, 0x98, 0)) {
                goto clear_step;
            }
            break;
        case 10:
            Scene_SetupParty(3);
            g_SceneState.step_05 = 0xB;
            break;
        case 11:
            if (D_80146867 != 0x18) {
                break;
            }
            UI_SetMode(0);
            g_SceneState.step_05 = 0xC;
            break;
        case 12:
            if (g_UiWindowEffectBusy) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(0x14);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0xD;
            break;
        case 13:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 0xE;
            break;
        case 14:
            SYS_SetFlag(g_SceneEventFlags, 0x46);
            Game_RequestAreaChange(AREA_ID_CAER_XHAN_LIFT_RIDE, TO_COORD(28), TO_COORD(12), AREA_ENTRY_MAP_LOADING | FACING_UP_LEFT);
            g_GameEntryMode      = GAME_NONE;
            g_GameRequestKind    = GAME_NONE;
            g_GamePrevSelection  = 0x27;
            g_SceneState.step_05 = 0xF;
            break;
        case 15:
            if (g_UiWindowEffectBusy) {
                break;
            }
            D_801FC4C0 = Actor_FindFreeSpawned();
            if (D_801FC4C0 != GAME_NONE) {
                g_SpawnedActors[D_801FC4C0].header.flags = 1;
                g_SpawnedActors[D_801FC4C0].type         = 0x8D;
            }
            func_801F924C();
            g_AreaDrawFlags = 0x1F;
            UI_SetMode(1);
            g_SceneState.step_05 = 0x10;
            break;
        case 16:
            if (g_UiWindowEffectBusy) {
                break;
            }
            func_801F924C();
            Message_StartAreaMessage(1);
            g_GameStateIndex                        = GAME_REQUEST_MESSAGE;
            g_SpawnedActors[D_801FC4C0].header.mode = 2;
            g_SceneState.step_05                    = 0x11;
            break;
        case 17:
            func_801F924C();
            break;
        case 18:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if ((u8)Scene_SpawnActor(0x13, -0x4BA, g_AreaCameraAngle.vy, 0x360, 0x78, 0)) {
                    g_SceneState.timer_06 = 0x50;
                    g_SceneState.step_05  = 0x13;
                    g_AreaCameraStep /= 2;
                }
            }
            func_801F924C();
            break;
        case 19:
            g_SceneState.timer_06--;
            if (g_SceneState.timer_06 == 0) {
                UI_SetMode(0);
                g_SceneState.step_05 = 0x14;
            }
            func_801F924C();
            break;
        case 20:
            if (g_UiWindowEffectBusy) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(2);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 0x16;
            break;
        case 22:
            D_80146867 = 0x20;
            Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(40), TO_COORD(99), 0x8A);
            g_GameEntryMode      = GAME_NONE;
            g_GameRequestKind    = GAME_NONE;
            g_GamePrevSelection  = GAME_NONE;
            g_SceneState.step_05 = 0x17;
            break;
        case 23:
            if (g_UiWindowEffectBusy) {
                break;
            }
            UI_SetMode(1);
            g_AreaDrawFlags = 0x1F;
            SND_RequestBGM(0x8C);
            g_SceneState.step_05 = 0x18;
            break;
        case 24:
            mode = &D_80146867;
            if (*mode != 0x31) {
                break;
            }
            if (EMI_IsReady() == 0) {
                break;
            }
            (*mode)++;
            SYS_SetFlag(g_SceneFlags, 0x11);
        clear_step:
            g_SceneState.state_04 = 0;
            g_SceneState.step_05  = 0;
            break;
    }
}

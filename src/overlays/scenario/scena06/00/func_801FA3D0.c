#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA3D0(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_SceneState.step_05 = 1;
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 1;
                g_SceneState.step_05 = 3;
            }
            break;
        case 1:
        case 3:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_SceneState.step_05 = 5;
            SYS_SetFlag(g_SceneFlags, 29);
            g_ScriptVars[2] = 4;
            g_SceneState.flags_01 |= 0x01;
            Game_RequestAreaChange(AREA_ID_BEYD_TRAINING, TO_COORD(24), TO_COORD(61), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP);
            g_GamePrevSelection = 0x3C;
            break;
        case 5:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            Battle_StartScripted(27);
            g_SceneState.step_05 = 6;
            break;
        case 7:
            func_801BE1B0(14);
            g_SceneState.step_05 = 10;
            SYS_SetFlag(g_SceneFlags, 31);
            Game_RequestAreaChange(AREA_ID_BEYD_TRAINING, TO_COORD(24), TO_COORD(60), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP_RIGHT);
            g_GamePrevSelection = 0xFF;
            break;
        case 10:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            func_801C16B8();
            g_ScriptVars[2]      = 2;
            g_SceneState.step_05 = 6;
            g_SceneState.flags_01 ^= 0x01;
            Game_RequestAreaChange(AREA_ID_RHAPALA_WORLD_MAP, TO_COORD(49), TO_COORD(45), FACING_DOWN_RIGHT);
            break;
        case 15:
            func_801BE1B0(11);
            g_SceneState.step_05 = 16;
            break;
        case 16:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            UI_SetMode(0xD);
            SYS_SetFlag(g_SceneFlags, 32);
            g_SceneState.step_05 = 17;
            break;
        case 17:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(0x2B);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 18;
            break;
        case 18:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801C16B8();
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 6;
                SYS_ClearFlag(g_SceneFlags, 29);
                g_SceneState.flags_01 ^= 0x01;
                Game_RequestAreaChange(AREA_ID_RHAPALA_WORLD_MAP, TO_COORD(49), TO_COORD(45), FACING_DOWN_RIGHT);
            }
            break;
        case 20:
            func_801BE1B0(13);
            g_SceneState.step_05 = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            UI_SetMode(0xD);
            SYS_SetFlag(g_SceneFlags, 32);
            g_SceneState.step_05 = 22;
            break;
        case 22:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(0x29);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 23;
            break;
        case 23:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801C16B8();
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 6;
                SYS_ClearFlag(g_SceneFlags, 29);
                g_SceneState.flags_01 ^= 0x01;
                Game_RequestAreaChange(AREA_ID_RHAPALA_WORLD_MAP, TO_COORD(49), TO_COORD(45), FACING_DOWN_RIGHT);
            }
            break;
    }
}

#include "area193_13.h"

MATCH void func_801F2EA0(void) {
    switch (g_SceneEventStep) {
        case 0:
            break;
        case 10:
            Message_StartAreaMessage(0x1C);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_SceneEventStep = 0xB;
            break;
        case 12:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                u8* flag;

                SYS_ClearFlag(g_SceneEventFlags, 0x77);
                Game_ClearScriptActive();
                Game_RequestAreaChange(AREA_ID_DESERT_OF_DEATH_MAP, TO_COORD(0x1200), TO_COORD(0x17FF), FACING_UP_RIGHT);
                D_8014504B = 2;
                D_80144F57 = 0xF0;
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                D_80144F54       = 0;
                D_80144F56       = 0;
                D_80146880       = 0;
                D_80146881       = 0;
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
                flag             = &g_SceneState.flags_01;
                *flag |= 1;
            }
            break;
        case 14:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SYS_ClearFlag(g_SceneEventFlags, 0x77);
                Game_ClearScriptActive();
                Game_RequestAreaChange(AREA_ID_KOMBINAT_WORLD_MAP, TO_COORD(0x16), TO_COORD(0x15), FACING_RIGHT);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 16:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                Message_StartAreaMessage(SYS_TestFlag(&g_Scenario2Flags[0x60], 3) ? 0x25 : 0x20);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                g_SceneEventStep = 0x15;
            }
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Char_RebuildPartyStats();
                SND_StartXAStream(0, 1);
                g_SceneEventStep = 0x16;
            }
            break;
        case 22:
            if ((SND_IsXAIdle() & BYTE_MASK) != 0) {
                u8* flags;

                g_ScriptVars[0] = 1;
                SND_StartBGM(0x95, 100, 0x10);
                UI_SetMode(UI_MODE_FADE_IN);
                flags           = &g_Scenario2Flags[0x60];
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                SYS_ClearFlag(flags, 3);
                SYS_ClearFlag(flags + 0x30, 0x8A);
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
    }
}

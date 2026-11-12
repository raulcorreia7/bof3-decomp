#include "area192_13.h"

MATCH void func_801F2E98(void) {
    switch (g_SceneEventStep) {
        case 0:
            Message_StartAreaMessage(0x6D);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_SceneEventStep = 1;
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_SetMode(UI_MODE_FADE_OUT);
                g_SceneEventStep = 3;
            }
            break;
        case 3:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
                SND_PauseBGM(g_SndBGMId);
                func_801F3548();
                SND_StartXAStream(0, 1);
                g_SceneEventStep = 4;
            }
            break;
        case 4:
            if ((SND_IsXAIdle() & BYTE_MASK) != 0) {
                u8* flag;
                u8  flag_value;

                SYS_SetFlag(g_SceneEventFlags, 0x82);
                D_80144F54 = 0x1E0;
                flag       = &g_SceneState.flags_01;
                D_80146880 = 0;
                D_80146881 = 0;
                /* FAKE: barrier keeps the flag load below the zero stores. */
                FAKE_BARRIER();
                flag_value       = *flag;
                g_SceneEventStep = 0xA;
                flag_value &= ~1;
                *flag = flag_value;
            }
            break;
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                u16* area;

                Game_ClearScriptActive();
                area = &D_80145048;
                Game_RequestAreaChange(*area, D_80145040, D_80145044, FACING_DOWN_RIGHT);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                D_8014504A = 0;
                /* The scene-event flag block sits 0x120 bytes before the saved area id. */
                SYS_ClearFlag((u8*)area - 0x120, 0x77);
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 30:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                s8* word;
                u8* flag;
                u8  value;

                Game_ClearScriptActive();
                Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD(24), TO_COORD(48), FACING_UP);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                word  = &D_8014504A;
                *word = 0;
                /* The scene-event flag block sits 0x122 bytes before the saved area byte. */
                SYS_ClearFlag((u8*)word - 0x122, 0x77);
                flag             = &g_SceneState.flags_01;
                value            = *flag;
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
                value &= ~1;
                *flag = value;
            }
            break;
    }
}

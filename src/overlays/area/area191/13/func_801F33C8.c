#include "area191_13.h"
#include "menu/save_data.h"

MATCH void func_801F33C8(void) {
    switch (g_SceneEventState.step) {
        case 0:
            MESSAGE_START_WAIT(MSG_AREA191_ASK_BREAK_CAMP);
            g_SceneEventState.step = 1;
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                UI_ModeSet(UI_MODE_FADE_OUT);
                g_SceneEventState.step = 3;
            }
            break;
        case 3:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
                SND_BGMPause(g_SndBGMId);
                func_801F3AB0();
                SND_XAStartStream(0, 1);
                g_SceneEventState.step = 4;
            }
            break;
        case 4:
            if ((SND_XAIsIdle() & BYTE_MASK) != 0) {
                u8* flag;
                FAKE_REG(u8, counter, "v0"); /* FAKE: retail keeps the counter in v0. */
                u8 flag_value;

                SYS_SetFlag(g_SceneEventFlags, 0x82);
                /* FAKE: statement boundary holds the step store above the counter loads. */
                do {
                    g_SceneEventState.step = 0xA;
                } while (0);
                counter    = D_80144F56;
                flag       = &g_ScenarioState.flags_01;
                D_80144F54 = 0;
                D_80146880 = 0;
                D_80146881 = 0;
                /* FAKE: barrier keeps the flag load below the zero stores. */
                FAKE_BARRIER();
                flag_value = *flag;
                counter++;
                flag_value |= 1;
                D_80144F56 = counter;
                *flag      = flag_value;
            }
            break;
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                u16* area;

                Game_ClearScriptActive();
                area = &g_SaveData.return_point.area_id;
                Game_RequestAreaChange(*area, g_SaveData.return_point.x, g_SaveData.return_point.y, FACING_DOWN_RIGHT);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                g_SaveData.return_point.pending = 0;
                /* The scene-event flag block sits 0x120 bytes before the saved area id. */
                SYS_ClearFlag((u8*)area - 0x120, 0x77);
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 20:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
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
                word  = &g_SaveData.return_point.pending;
                *word = 0;
                /* The scene-event flag block sits 0x122 bytes before the saved area byte. */
                SYS_ClearFlag((u8*)word - 0x122, 0x77);
                flag                   = &g_ScenarioState.flags_01;
                value                  = *flag;
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
                value &= ~1;
                *flag = value;
            }
            break;
    }
}

#include "area189_13.h"
#include "area/map.h"

MATCH void func_801F4D14(void) {
    u8* flags;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        flags  = &g_SceneState.flags_01;
        *flags = *flags & 0xFE;
        if (g_SaveData.scene_event.step != 0) {
            Game_RequestAreaChange(AREA_ID_OASIS, 0x180000, 0x300000, 1);
        } else {
            Game_RequestAreaChange(AREA_ID_DESERT_ENTRANCE_CAMP, 0x1A8000, 0x1C0000, 1);
        }
        g_SaveData.scene_event.mode = 0;
        g_SaveData.scene_event.step = 0;
    }
}

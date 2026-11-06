#include "area106_13.h"

MATCH void func_801F3E54(s32 state) {
    Game_SetScriptActive();
    g_SaveData.scene_event.mode = 0x24;
    g_SaveData.scene_event.step = state;
}

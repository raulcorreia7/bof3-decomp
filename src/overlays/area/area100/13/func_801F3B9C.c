#include "area100_13.h"

MATCH void func_801F3B9C(void) {
    SYS_SetFlag(g_SaveData.scene_event_flags, 0x40);
    Area_SetCellPalette(0x4A, 0x2F);
    Game_SetScriptActive();
    g_SaveData.scene_event.mode = 0x1C;
    g_SaveData.scene_event.step = 0;
}

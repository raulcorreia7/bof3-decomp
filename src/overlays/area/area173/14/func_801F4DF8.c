#include "area173_14.h"

MATCH s32 func_801F4DF8(s32 entry_x, s32 entry_y) {
    if ((D_80143F03 == 1 && entry_y == 0x460000 && (entry_x >> 16) >= 0x11 && (entry_x >> 16) <= 0x13) ||
        (D_80143F03 == 2 && entry_y == 0x600000 && (entry_x >> 16) >= 0x30 && (entry_x >> 16) <= 0x32)) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode = 0x26;
        g_SaveData.scene_event.step = 0;
        return 1;
    }
    return 0;
}

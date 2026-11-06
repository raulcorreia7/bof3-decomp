#include "area150_13.h"

MATCH u8 func_801F2F58(s32 x, s32 y) {
    if ((u32)((x >> 16) - 0x17) < 6 && (u32)((y >> 16) - 0x33) < 6) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode = 0x3A;
        g_SaveData.scene_event.step = 0xA;
        return 1;
    }
    return 0;
}

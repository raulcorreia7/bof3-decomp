#include "area148_13.h"

MATCH u8 func_801F4108(s32 x, s32 y) {
    if ((y >> 16) == 0x1C && (u32)((x >> 16) - 0x12) < 3) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x1F;
        g_SceneEventStep = 0;
        return 1;
    }
    return 0;
}

#include "area197_13.h"

MATCH s32 func_801F41F4(s32 entry_x, s32 entry_y) {
    if (D_80143F03 == 4) {
        if ((((entry_y == 0x708000) || (entry_y == 0x738000)) && (((entry_x >> 0x10) - 3) < 3U)) ||
            ((entry_x == 0x28000) && (((entry_y >> 0x10) - 0x71) < 3U)) ||
            ((entry_x == 0x58000) && (((entry_y >> 0x10) - 0x71) < 3U))) {
            if (Item_VitalHas(0xD) != 0) {
                Game_SetScriptActive();
                g_SaveData.scene_event.mode = 0x33;
                g_SaveData.scene_event.step = 0;
                return 1;
            }
        } else if (!((entry_x == 0xD8000) && (((entry_y >> 0x10) - 0x71) < 2U) && (Item_VitalHas(0xD) == 0))) {
            return 0;
        }
        Game_SetScriptActive();
        D_80146874 = 5;
        D_80146875 = 0x14;
        return 1;
    }
    return 0;
}

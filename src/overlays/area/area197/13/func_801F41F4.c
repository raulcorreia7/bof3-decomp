#include "area197_13.h"

MATCH s32 func_801F41F4(s32 entry_x, s32 entry_y) {
    if (D_80143F03 == 4) {
        if ((((entry_y == 0x708000) || (entry_y == 0x738000)) && ((u32)((entry_x >> 0x10) - 3) < 3U)) ||
            ((entry_x == 0x28000) && ((u32)((entry_y >> 0x10) - 0x71) < 3U)) ||
            ((entry_x == 0x58000) && ((u32)((entry_y >> 0x10) - 0x71) < 3U))) {
            if (Party_HasVitalItem(0xD) != 0) {
                Game_SetScriptActive();
                D_801448EB = 0x33;
                D_801448EC = 0;
                return 1;
            }
        } else if (!((entry_x == 0xD8000) && ((u32)((entry_y >> 0x10) - 0x71) < 2U) &&
                     (Party_HasVitalItem(0xD) == 0))) {
            return 0;
        }
        Game_SetScriptActive();
        D_80146874 = 5;
        D_80146875 = 0x14;
        return 1;
    }
    return 0;
}

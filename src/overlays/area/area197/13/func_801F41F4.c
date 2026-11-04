#include "area197_13.h"

MATCH s32 func_801F41F4(s32 arg0, s32 arg1) {
    if (D_80143F03 == 4) {
        if ((((arg1 == 0x708000) || (arg1 == 0x738000)) && ((u32)((arg0 >> 0x10) - 3) < 3U)) ||
            ((arg0 == 0x28000) && ((u32)((arg1 >> 0x10) - 0x71) < 3U)) ||
            ((arg0 == 0x58000) && ((u32)((arg1 >> 0x10) - 0x71) < 3U))) {
            if (Party_HasVitalItem(0xD) != 0) {
                Game_SetScriptActive();
                D_801448EB = 0x33;
                D_801448EC = 0;
                return 1;
            }
        } else if (!((arg0 == 0xD8000) && ((u32)((arg1 >> 0x10) - 0x71) < 2U) && (Party_HasVitalItem(0xD) == 0))) {
            return 0;
        }
        Game_SetScriptActive();
        D_80146874 = 5;
        D_80146875 = 0x14;
        return 1;
    }
    return 0;
}

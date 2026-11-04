#include "area075_13.h"

MATCH s32 func_801F3F68(s32 entry_x, s32 entry_y) {
    if (!SYS_TestFlag(&D_80144ED8, 2)) {
        if (entry_x <= 0x1B0000) {
            if ((entry_y >> 16) >= 0x38 && (entry_y >> 16) <= 0x3B) {
                Game_SetScriptActive();
                D_80146867 = 10;
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

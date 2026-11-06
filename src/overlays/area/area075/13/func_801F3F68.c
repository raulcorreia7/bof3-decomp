#include "area075_13.h"

MATCH s32 func_801F3F68(s32 entry_x, s32 entry_y) {
    if (!SYS_TestFlag(&D_80144ED8, 2) && entry_x <= TO_COORD(27) && (entry_y >> 16) >= 56 && (entry_y >> 16) <= 59) {
        Game_SetScriptActive();
        D_80146867 = 10;
        return 1;
    }
    return 0;
}

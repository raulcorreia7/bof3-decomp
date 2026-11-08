#include "area167_13.h"

MATCH u8 func_801F48B4(s32 x, s32 y) {
    if ((y >> 16) == 102 && (u32)((x >> 16) - 20) < 3) {
        Scene_StartEvent(0x20, 0);
        return 1;
    }
    return 0;
}

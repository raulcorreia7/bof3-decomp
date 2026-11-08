#include "area150_13.h"

MATCH u8 func_801F2F58(s32 x, s32 y) {
    if ((u32)((x >> 16) - 23) < 6 && (u32)((y >> 16) - 51) < 6) {
        Scene_StartEvent(0x3A, 0xA);
        return 1;
    }
    return 0;
}

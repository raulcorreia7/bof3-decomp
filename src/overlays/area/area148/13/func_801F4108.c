#include "area148_13.h"

MATCH u8 func_801F4108(s32 x, s32 y) {
    if ((y >> 16) == 28 && (u32)((x >> 16) - 18) < 3) {
        Scene_StartEvent(0x1F, 0);
        return 1;
    }
    return 0;
}

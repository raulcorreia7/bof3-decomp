#include "area173_14.h"

MATCH s32 func_801F4DF8(s32 entry_x, s32 entry_y) {
    if ((D_80143F03 == 1 && entry_y == TO_COORD(70) && (entry_x >> 16) >= 17 && (entry_x >> 16) <= 19) ||
        (D_80143F03 == 2 && entry_y == TO_COORD(96) && (entry_x >> 16) >= 48 && (entry_x >> 16) <= 50)) {
        Scene_StartEvent(0x26, 0);
        return 1;
    }
    return 0;
}

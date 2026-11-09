#include "area172_13.h"

/* Script condition: with D_80143F03 clear, x is exactly 0x248000, y falls in the 0x35..0x37 block and g_Game.members[0].facing is 0, 6 or 7. */
MATCH s32 func_801F4CC4(s32 x, s32 y) {
    if (D_80143F03 == 0) {
        if (x == TO_COORD(36) + COORD_HALF && ((y >> 16) - 53) < 3U &&
            ((g_Game.members[0].facing - 6) < 2U || g_Game.members[0].facing == FACING_UP_LEFT)) {
            Scene_StartEvent(0x23, 0);
            return 1;
        }
    }
    return 0;
}

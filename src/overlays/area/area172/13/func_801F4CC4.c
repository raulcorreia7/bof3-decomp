#include "area172_13.h"

/* Script condition: with D_80143F03 clear, x is exactly 0x248000, y falls in the
 * 0x35..0x37 block and D_80145E98 is 0, 6 or 7; the match starts the script and
 * queues D_801448EB = 0x23. */
MATCH s32 func_801F4CC4(s32 x, s32 y) {
    if (D_80143F03 == 0) {
        if (x == 0x248000 && (u32)((y >> 16) - 0x35) < 3U && ((u32)(D_80145E98 - 6) < 2U || D_80145E98 == 0)) {
            Game_SetScriptActive();
            D_801448EB = 0x23;
            D_801448EC = 0;
            return 1;
        }
    }
    return 0;
}

#include "area030_04.h"

/* When the mode byte `g_FishingNewRecord` is set and bit 0x8 of the shared
 * state word `g_FrameCount` is set, selects graphics mode 3/1 and routes the
 * marker helper `Fishing_DrawSprite` for id 0x47 at (0x1A, 0x5C). */
MATCH void func_801E1C7C(void) {
    if (g_FishingNewRecord == 0) {
        return;
    }
    if ((g_FrameCount & 0x8) == 0) {
        return;
    }
    Fishing_SetDrawMode(3, 1);
    Fishing_DrawSprite(71, 1, 26, 92);
}

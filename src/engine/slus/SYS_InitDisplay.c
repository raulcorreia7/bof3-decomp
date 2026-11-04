#include "engine/slus/slus.h"

/* initializes both display/draw environment pairs used by the
 * boot-side double buffer.
 */
MATCH void SYS_InitDisplay(void) {
    u8* work;

    work = g_GfxDisplayFrames + 0x14;
    SetDefDrawEnv((DRAWENV*)work, 0, 0, 320, 240);
    SetDefDispEnv((DISPENV*)(work - 0x14), 0, 240, 320, 240);
    SetDefDrawEnv((DRAWENV*)(work + 0x90), 0, 240, 320, 240);
    SetDefDispEnv((DISPENV*)(work + 0x7C), 0, 0, 320, 240);
}

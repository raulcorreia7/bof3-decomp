#include "engine/slus/slus.h"

/* clears one frame's ordering table and arms its draw environment to clear the background to black.
 */
MATCH void SYS_ResetDisplayFrame(u8* work) {
    DRAWENV* draw;

    ClearOTagR((u_long*)(work + 0x70), 8);
    draw       = (DRAWENV*)(work + 0x14);
    draw->isbg = 1;
    draw->r0   = 0;
    draw->g0   = 0;
    draw->b0   = 0;
}

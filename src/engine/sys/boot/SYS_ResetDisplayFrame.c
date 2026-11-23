#include "engine/slus/slus.h"

/* clears one frame's ordering table and arms its draw environment to clear the background to black.
 */
MATCH void SYS_ResetDisplayFrame(struct GfxFrame* frame) {
    DRAWENV* draw;

    ClearOTagR(frame->ot, 8);
    draw       = &frame->draw;
    draw->isbg = 1;
    draw->r0   = 0;
    draw->g0   = 0;
    draw->b0   = 0;
}

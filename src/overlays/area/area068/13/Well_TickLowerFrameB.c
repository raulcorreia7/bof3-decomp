#include "area068_13.h"

/* Twin of Well_TickLowerFrameA in this image (cue 0x200, task modes 3 and 1
 * swapped); consolidate the bodies in the polish pass. */
/* func_801F2E68 */
MATCH void Well_TickLowerFrameB(void) {
    if (--g_WellLowerTimer == 0) {
        SND_PlayCue(0x200);
        g_WellLowerTimer    = 0;
        g_WellLowerCount    = g_WellPressCount;
        g_Task->header.mode = 0xA;
    } else if (g_InputPressed == PADRup) {
        g_WellIdleFrames = 0;
        g_WellPressCount += 1;
        g_Task->header.mode = 3;
    } else {
        g_Task->header.mode = 1;
    }
}

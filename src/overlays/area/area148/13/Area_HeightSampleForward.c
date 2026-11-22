#include "area148_13.h"

/* func_801F4544 */
MATCH void Area_HeightSampleForward(void) {
    s32 y;

    TASK(Actor)->unk_18  = TASK(Actor)->pos.x.fixed + (g_FacingSteps[TASK(Actor)->direction].x * 5);
    y                    = TASK(Actor)->pos.y.fixed + (g_FacingStepY[TASK(Actor)->direction * 2] * 5);
    TASK(Actor)->unk_1C  = y;
    TASK(Actor)->gravity = Area_HeightSample(TASK(Actor)->unk_18, y) << 0x10;
}

#include "area148_13.h"

/* func_801F4544 */
MATCH void Area_HeightSampleForward(void) {
    s32 y;

    SELF(Actor)->unk_18  = SELF(Actor)->pos.x.fixed + (g_FacingSteps[SELF(Actor)->direction].x * 5);
    y                    = SELF(Actor)->pos.y.fixed + (g_FacingStepY[SELF(Actor)->direction * 2] * 5);
    SELF(Actor)->unk_1C  = y;
    SELF(Actor)->gravity = Area_HeightSample(SELF(Actor)->unk_18, y) << 0x10;
}

#include "area148_13.h"

/* func_801F4544 */
MATCH void Area_HeightSampleForward(void) {
    s32 y;

    (g_Task)->unk_18  = (g_Task)->pos.x.fixed + (g_FacingSteps[(g_Task)->direction].x * 5);
    y                 = (g_Task)->pos.y.fixed + (g_FacingStepY[(g_Task)->direction * 2] * 5);
    (g_Task)->unk_1C  = y;
    (g_Task)->gravity = Area_HeightSample((g_Task)->unk_18, y) << 0x10;
}

#include "engine/slus/slus.h"

/* adds the work record's 0x14 speed accumulator high byte to the 0x3E distance counter, advances the
 * accumulator by the signed step and measures the distance to the record coordinates; while the counter is below it,
 * raises it to the measurement and clears the 0x04 state byte (returns 0), else returns 1.
 */
MATCH s32 Actor_RiseToGround(s32 entry, s32 dir_x, s32 dir_y, s32 vz_start, s16 vz_step) {
    s16 distance;

    g_Task->z.part.integer = (g_Task->z.part.integer + (g_Task->vz >> 8));
    g_Task->vz             = g_Task->vz + vz_step;
    distance               = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    if (g_Task->z.part.integer < distance) {
        g_Task->z.part.integer = distance;
        g_Task->unk_04         = 0;
        return 0;
    }
    return 1;
}

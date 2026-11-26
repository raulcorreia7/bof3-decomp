#include "engine/slus/slus.h"

/* adds the work record's 0x14 speed accumulator high byte to the 0x3E distance counter, advances the
 * accumulator by the signed step and measures the distance to the record coordinates; while the counter is below it,
 * raises it to the measurement and clears the 0x04 state byte (returns 0), else returns 1.
 */
MATCH s32 Actor_RiseToGround(s32 entry, s32 dir_x, s32 dir_y, s32 vz_start, s16 vz_delta) {
    s16 distance;

    COORD_INT(SELF(Actor)->pos.z) += (SELF(Actor)->vz >> 8);
    SELF(Actor)->vz = SELF(Actor)->vz + vz_delta;
    distance        = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if (COORD_INT(SELF(Actor)->pos.z) < distance) {
        COORD_INT(SELF(Actor)->pos.z) = (u16)distance;
        SELF(Actor)->unk_04           = 0;
        return 0;
    }
    return 1;
}

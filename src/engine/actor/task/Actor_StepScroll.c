#include "engine/slus/slus.h"

/* advances the scratchpad work cursor, refreshes the staged view, and
 * switches the active stream record when the cursor expires and the limit
 * reaches the next script position.
 */
MATCH s8 Actor_StepScroll(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags) {
    s16 limit;

    COORD_INT(SELF(Actor)->pos.z) += (SELF(Actor)->vz >> 8);
    SELF(Actor)->vz = SELF(Actor)->vz + vz_delta;
    Area_ScrollAdvance(COORD_INT(g_PartyPos.z));
    SELF(Actor)->unk_0A = SELF(Actor)->unk_0A - 1;
    limit               = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
    if (SELF(Actor)->vz < 0 && limit > COORD_INT(SELF(Actor)->pos.z)) {
        COORD_INT(SELF(Actor)->pos.z) = (u16)limit;
        Area_ScrollAdvance(limit);
        /* FAKE: the single-pass block homes flags in s1 and entry in s2. */
        do {
            if (flags & 0x2) {
                SELF(Actor)->unk_04 = 0;
            }
        } while (0);
    }
    if (SELF(Actor)->unk_0A == 0) {
        if (SELF(Actor)->param.unk_0B != 0) {
            SELF(Actor)->unk_0A       = 0x10 / (s32)g_RouteSpeedScale[((u8*)entry)[4]];
            SELF(Actor)->param.unk_0B = SELF(Actor)->param.unk_0B - 1;
        } else {
            if (limit >= COORD_INT(SELF(Actor)->pos.z)) {
                /* FAKE: byte-view stores keep the g_AreaScrollTargetY load after the 0x34 store. */
                FIELD(s32, g_Self, 0x34)      = g_AreaScrollTargetX;
                COORD_INT(SELF(Actor)->pos.z) = limit;
                SELF(Actor)->pos.y.fixed      = g_AreaScrollTargetY;
                Area_ScrollAdvance(limit);
                SELF(Actor)->unk_04 = 0;
                return 0;
            }
            SELF(Actor)->unk_0A = 1;
        }
    }
    return 1;
}

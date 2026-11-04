#include "engine/slus/slus.h"

/* advances the scratchpad work cursor, refreshes the staged view, and
 * switches the active stream record when the cursor expires and the limit
 * reaches the next script position.
 */
MATCH s8 Actor_StepScroll(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, s32 flags) {
    s16 limit;

    g_SpadWork->z.part.integer = (u16)(g_SpadWork->z.part.integer + (g_SpadWork->vz >> 8));
    g_SpadWork->vz             = g_SpadWork->vz + vz_step;
    Area_AdvanceScroll(g_ScrollHeight[0]);
    g_SpadWork->unk_0A = g_SpadWork->unk_0A - 1;
    limit              = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
    if (g_SpadWork->vz < 0 && limit > g_SpadWork->z.part.integer) {
        g_SpadWork->z.part.integer = (u16)limit;
        Area_AdvanceScroll(limit);
        /* FAKE: the single-pass block homes flags in s1 and entry in s2. */
        do {
            if (flags & 2) {
                g_SpadWork->unk_04 = 0;
            }
        } while (0);
    }
    if (g_SpadWork->unk_0A == 0) {
        if (g_SpadWork->unk_0B != 0) {
            g_SpadWork->unk_0A = 0x10 / (s32)g_RouteSpeedScale[((u8*)entry)[4]];
            g_SpadWork->unk_0B = g_SpadWork->unk_0B - 1;
        } else {
            if (limit >= g_SpadWork->z.part.integer) {
                /* FAKE: byte-view stores keep the g_AreaScrollTargetY load after the 0x34 store. */
                FIELD(s32, g_SpadWork, 0x34) = g_AreaScrollTargetX;
                g_SpadWork->z.part.integer   = limit;
                FIELD(s32, g_SpadWork, 0x38) = g_AreaScrollTargetY;
                Area_AdvanceScroll(limit);
                g_SpadWork->unk_04 = 0;
                return 0;
            }
            g_SpadWork->unk_0A = 1;
        }
    }
    return 1;
}

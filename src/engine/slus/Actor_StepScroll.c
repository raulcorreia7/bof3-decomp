#include "engine/slus/slus.h"

/* advances the scratchpad work cursor, refreshes the staged view, and
 * switches the active stream record when the cursor expires and the limit
 * reaches the next script position.
 */
MATCH s8 Actor_StepScroll(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags) {
    s16 limit;

    COORD_INT(g_Task->pos.z) += (g_Task->vz >> 8);
    g_Task->vz = g_Task->vz + vz_delta;
    Area_AdvanceScroll(g_ScrollHeight[0]);
    g_Task->unk_0A = g_Task->unk_0A - 1;
    limit          = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
    if (g_Task->vz < 0 && limit > COORD_INT(g_Task->pos.z)) {
        COORD_INT(g_Task->pos.z) = (u16)limit;
        Area_AdvanceScroll(limit);
        /* FAKE: the single-pass block homes flags in s1 and entry in s2. */
        FAKE_ORDER_LOCK_BEGIN
            if (flags & 0x2) {
                g_Task->unk_04 = 0;
            }
        FAKE_ORDER_LOCK_END;
    }
    if (g_Task->unk_0A == 0) {
        if (g_Task->param.unk_0B != 0) {
            g_Task->unk_0A       = 0x10 / (s32)g_RouteSpeedScale[((u8*)entry)[4]];
            g_Task->param.unk_0B = g_Task->param.unk_0B - 1;
        } else {
            if (limit >= COORD_INT(g_Task->pos.z)) {
                /* FAKE: byte-view stores keep the g_AreaScrollTargetY load after the 0x34 store. */
                FIELD(s32, g_Task, 0x34) = g_AreaScrollTargetX;
                COORD_INT(g_Task->pos.z) = limit;
                FIELD(s32, g_Task, 0x38) = g_AreaScrollTargetY;
                Area_AdvanceScroll(limit);
                g_Task->unk_04 = 0;
                return 0;
            }
            g_Task->unk_0A = 1;
        }
    }
    return 1;
}

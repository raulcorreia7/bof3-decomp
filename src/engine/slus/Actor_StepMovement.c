#include "engine/slus/slus.h"

/* steps the scratchpad work record: it adds the unk_0C delta to
 * unk_34 and the unk_10 delta to unk_38, adds the old unk_14 shifted right by
 * eight to unk_3E, counts unk_0A down and adds the incoming step to unk_14;
 * it keeps the larger ground height in unk_3E, and when unk_0A runs out it writes
 * 0x10 divided by the byte from g_RouteSpeedScale into unk_0A, or calls
 * func_8015C9CC and sets unk_04 to 3.
 */
MATCH s8 Actor_StepMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, u8 flags) {
    Actor* work;
    s32    speed;
    s16    height;
    u8     count;
    s32    sum;

    work          = g_SpadWork;
    speed         = work->vz;
    sum           = work->x.fixed;
    count         = work->unk_0A - 1;
    work->x.fixed = sum + work->unk_0C;
    work->y.fixed += work->unk_10;
    work->z.part.integer += work->vz >> 8;
    work->unk_0A = count;
    work->vz     = speed + vz_step;
    height       = Area_SampleHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
    if (g_SpadWork->vz < 0 && height > g_SpadWork->z.part.integer) {
        g_SpadWork->z.part.integer = height;
        if (flags & 2) {
            g_SpadWork->unk_04 = 0;
            return 0;
        }
    }
    if (g_SpadWork->vz <= 0 && speed >= 0 && landing_script != GAME_NONE) {
        if (g_SpadWork->unk_06 != 6) {
            g_SpadWork->unk_2A = flags & 1;
        }
        Actor_RequestScript(landing_script);
    }
    if (g_SpadWork->unk_0A == 0) {
        if (g_SpadWork->unk_0B != 0) {
            g_SpadWork->unk_0A = 0x10 / g_RouteSpeedScale[FIELD(u8, (void*)entry, 0x4u)];
            g_SpadWork->unk_0B -= 1;
        } else {
            Actor_ApplyVelocity();
            g_SpadWork->unk_04 = 3;
        }
    }
    func_801A3D1C((void*)entry);
    return 1;
}

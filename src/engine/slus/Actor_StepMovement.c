#include "engine/slus/slus.h"

/* steps the scratchpad work record: it adds vx to x and vy to y, adds the old vz shifted right by eight
 * to the z integer, counts unk_0A down and adds the incoming step to vz; it keeps the larger ground
 * height in the z integer, and when unk_0A runs out it writes 0x10 divided by the byte from
 * g_RouteSpeedScale into unk_0A, or calls Actor_ApplyVelocity and sets unk_04 to 3.
 */
MATCH s8 Actor_StepMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_step, u8 landing_script, u8 flags) {
    Actor* work;
    s32    speed;
    s16    height;
    u8     count;
    s32    sum;

    work          = g_Task;
    speed         = work->vz;
    sum           = work->x.fixed;
    count         = work->unk_0A - 1;
    work->x.fixed = sum + work->vx;
    work->y.fixed += work->vy;
    work->z.part.integer += work->vz >> 8;
    work->unk_0A = count;
    work->vz     = speed + vz_step;
    height       = Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    if (g_Task->vz < 0 && height > g_Task->z.part.integer) {
        g_Task->z.part.integer = height;
        if (flags & 2) {
            g_Task->unk_04 = 0;
            return 0;
        }
    }
    if (g_Task->vz <= 0 && speed >= 0 && landing_script != GAME_NONE) {
        if (g_Task->unk_06 != 6) {
            g_Task->unk_2A = flags & 1;
        }
        Actor_RequestScript(landing_script);
    }
    if (g_Task->unk_0A == 0) {
        if (g_Task->unk_0B != 0) {
            g_Task->unk_0A = 0x10 / g_RouteSpeedScale[FIELD(u8, (void*)entry, 0x4u)];
            g_Task->unk_0B -= 1;
        } else {
            Actor_ApplyVelocity();
            g_Task->unk_04 = 3;
        }
    }
    func_801A3D1C((void*)entry);
    return 1;
}

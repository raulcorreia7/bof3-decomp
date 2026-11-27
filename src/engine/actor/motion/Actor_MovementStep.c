#include "engine/slus/slus.h"

/* steps the scratchpad work record: it adds vx to x and vy to y, adds the old vz shifted right by eight
 * to the z integer, counts unk_0A down and adds the incoming step to vz; it keeps the larger ground
 * height in the z integer, and when unk_0A runs out it writes 0x10 divided by the byte from
 * g_RouteSpeedScale into unk_0A, or calls Actor_ApplyVelocity and sets unk_04 to 3.
 */
MATCH s8 Actor_MovementStep(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, u8 flags) {
    Actor* work;
    s32    speed;
    s16    height;
    u8     count;
    s32    sum;

    work              = SELF(Actor);
    speed             = work->vz;
    sum               = work->pos.x.fixed;
    count             = work->unk_0A - 1;
    work->pos.x.fixed = sum + work->vx;
    work->pos.y.fixed += work->vy;
    COORD_INT(work->pos.z) += work->vz >> 8;
    work->unk_0A = count;
    work->vz     = speed + vz_delta;
    height       = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if (SELF(Actor)->vz < 0 && height > COORD_INT(SELF(Actor)->pos.z)) {
        COORD_INT(SELF(Actor)->pos.z) = height;
        if (flags & 0x2) {
            SELF(Actor)->unk_04 = 0;
            return 0;
        }
    }
    if (SELF(Actor)->vz <= 0 && speed >= 0 && landing_script != GAME_NONE) {
        if (SELF(Actor)->unk_06 != 6) {
            SELF(Actor)->mirror = flags & 0x1;
        }
        Script_Request(landing_script);
    }
    if (SELF(Actor)->unk_0A == 0) {
        if (SELF(Actor)->param.unk_0B != 0) {
            SELF(Actor)->unk_0A = 0x10 / g_RouteSpeedScale[FIELD(u8, (void*)entry, 0x4u)];
            SELF(Actor)->param.unk_0B -= 1;
        } else {
            Actor_ApplyVelocity();
            SELF(Actor)->unk_04 = 3;
        }
    }
    Actor_TurnRampStep((void*)entry);
    return 1;
}

#include "engine/slus/slus.h"

/* seeds the work area from the selected handler entry: the size byte
 * sets the hold counter and the two velocity dividers, and mode 2 instead
 * publishes the direction vector into the movement globals.
 */
MATCH s8 Actor_MovementInit(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags) {
    u8  size;
    s32 absX;
    s32 absY;
    u8  span;

    size = g_RouteSpeedScale[((u8*)entry)[4]];
    if (size == 0) {
        return 0;
    }
    absY               = abs(dir_y);
    SELF(Actor)->timer = 0;
    span               = absY;
    absX               = abs(dir_x);
    if (absX >= absY) {
        span = absX;
    }
    if (span != 0) {
        SELF(Actor)->param.unk_0B = span - 1;
    } else {
        SELF(Actor)->param.unk_0B = 0;
    }
    SELF(Actor)->unk_0A = 16 / size;
    SELF(Actor)->vz     = vz_start << 8;

    if ((u8)(Actor_GetOwner()) != 2) {
        if (span != 0) {
            SELF(Actor)->vx = (dir_x << 15) / (SELF(Actor)->unk_0A * span);
            SELF(Actor)->vy = (dir_y << 15) / (SELF(Actor)->unk_0A * span);
        } else {
            SELF(Actor)->vy = 0;
            SELF(Actor)->vx = 0;
        }
        SELF(Actor)->unk_04 = 1;
    } else {
        g_AreaCameraSpeed           = size * 8;
        g_AreaCameraHeightDelta     = 0;
        g_AreaCamera.scroll_x.fixed = g_PartyPos.x.fixed + (dir_x << 15);
        g_AreaCamera.scroll_y.fixed = g_PartyPos.y.fixed + (dir_y << 15);
        SELF(Actor)->unk_04         = 2;
    }
    return 1;
}

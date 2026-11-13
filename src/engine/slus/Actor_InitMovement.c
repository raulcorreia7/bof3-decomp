#include "engine/slus/slus.h"

/* seeds the work area from the selected handler entry: the size byte
 * sets the hold counter and the two velocity dividers, and mode 2 instead
 * publishes the direction vector into the movement globals.
 */
MATCH s8 Actor_InitMovement(s32 entry, s8 dir_x, s8 dir_y, s16 vz_start, s16 vz_delta, u8 landing_script, s32 flags) {
    u8  size;
    s32 absX;
    s32 absY;
    u8  span;

    size = g_RouteSpeedScale[((u8*)entry)[4]];
    if (size == 0) {
        return 0;
    }
    absY          = abs(dir_y);
    g_Task->timer = 0;
    span          = absY;
    absX          = abs(dir_x);
    if (absX >= absY) {
        span = absX;
    }
    if (span != 0) {
        g_Task->param.unk_0B = span - 1;
    } else {
        g_Task->param.unk_0B = 0;
    }
    g_Task->unk_0A = 16 / size;
    g_Task->vz     = vz_start << 8;

    if ((u8)(Actor_GetOwner()) != 2) {
        if (span != 0) {
            g_Task->vx = (dir_x << 15) / (g_Task->unk_0A * span);
            g_Task->vy = (dir_y << 15) / (g_Task->unk_0A * span);
        } else {
            g_Task->vy = 0;
            g_Task->vx = 0;
        }
        g_Task->unk_04 = 1;
    } else {
        g_AreaCameraStep       = size * 8;
        g_AreaCameraHeightStep = 0;
        g_AreaScrollTargetX    = g_PartyX + (dir_x << 15);
        g_AreaScrollTargetY    = g_PartyY + (dir_y << 15);
        g_Task->unk_04         = 2;
    }
    return 1;
}

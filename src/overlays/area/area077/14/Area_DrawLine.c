#include "area077_14.h"

/* func_801F3898 */
MATCH void Area_DrawLine(Pos2 first, Pos2 second, u8 shade) {
    Pos2 delta;
    Pos2 swap;
    s16  step;
    s16  error;
    u8   i;

    delta.vx = (second.vx > first.vx) ? second.vx - first.vx : first.vx - second.vx;
    delta.vy = (second.vy > first.vy) ? second.vy - first.vy : first.vy - second.vy;
    if (delta.vy < delta.vx || delta.vy == 0) {
        if (first.vx > second.vx) {
            swap   = first;
            first  = second;
            second = swap;
        }
        step  = (second.vy > first.vy) ? 1 : -1;
        error = -delta.vx;
        for (i = 0; i < delta.vx; i++) {
            func_801F3B48(&first, shade);
            first.vx++;
            error += (u16)delta.vy * 2;
            if (error > 0) {
                first.vy += step;
                error -= (u16)delta.vx * 2;
            }
        }
    } else {
        if (first.vy > second.vy) {
            swap   = first;
            first  = second;
            second = swap;
        }
        step  = (second.vx > first.vx) ? 1 : -1;
        error = -delta.vy;
        for (i = 0; i < delta.vy; i++) {
            func_801F3B48(&first, shade);
            first.vy++;
            error += (u16)delta.vx * 2;
            if (error > 0) {
                first.vx += step;
                error -= (u16)delta.vy * 2;
            }
        }
    }
}

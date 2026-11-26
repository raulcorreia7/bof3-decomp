#include "area/effects.h"

u32 MATH_AverageAngle(u16 a, u16 b);

/* Link headings follow the points; the shifted offset keeps the trail pointer first in the add. */
#define TRAIL_HEADING(trail, i) (*(u16*)((u8*)(trail) + ((i) << 1) + sizeof((trail)->point)))

/* func_801F8D98 */
/* Trail_Update (func_801F88B8 in scena07, func_801F8D98 in scena08, func_801F2F28 in area088): shifts the trail history, puts the task position first, projects every point to the screen and sets the point angles from the headings to their neighbours. Every change must verify every member. */
MATCH void Trail_Update(Trail* trail) {
    s8     i;
    s8     j;
    s32    prev;
    u16    size[2];
    u16    scale[2];
    MATRIX camera;

    for (i = 30; i >= 0; i--) {
        trail->point[i + 1] = trail->point[i];
    }
    setVector(&trail->point[0].pos, SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->pos.z.fixed);
    Camera_SetMatrix(&camera);
    for (i = 0; i < 32; i++) {
        Camera_ProjectPoint(&trail->point[i].pos.vx, &trail->point[i].screen);
        size[0] = size[1] = trail->width;
        Game_ProjectWorldPoint(&trail->point[i], size, scale);
        trail->point[i].width = scale[0];
    }
    for (i = 0; i < 31; i++) {
        scale[0] = trail->point[i].screen.vx - trail->point[i + 1].screen.vx;
        scale[1] = trail->point[i].screen.vy - trail->point[i + 1].screen.vy;
        if ((s16)scale[0] != 0 || (s16)scale[1] != 0) {
            TRAIL_HEADING(trail, i) = ratan2((s16)scale[1], (s16)scale[0]);
        } else {
            TRAIL_HEADING(trail, i) = TRAIL_HEADING_UNSET;
        }
    }
    for (i = 0; i < 31; i++) {
        if (TRAIL_HEADING(trail, i) != TRAIL_HEADING_UNSET) {
            continue;
        }
        for (j = i + 1; j < 31; j++) {
            if (TRAIL_HEADING(trail, j) != TRAIL_HEADING_UNSET) {
                TRAIL_HEADING(trail, i) = TRAIL_HEADING(trail, j);
                goto next;
            }
        }
        for (j = 0; j < i; j++) {
            if (TRAIL_HEADING(trail, j) != TRAIL_HEADING_UNSET) {
                TRAIL_HEADING(trail, i) = TRAIL_HEADING(trail, j);
                goto next;
            }
        }
        TRAIL_HEADING(trail, j) = 0;
    next:;
    }
    trail->point[0].angle = TRAIL_HEADING(trail, 0);
    for (i = 1; i < 31; i++) {
        prev                  = i - 1;
        trail->point[i].angle = MATH_AverageAngle(TRAIL_HEADING(trail, prev), TRAIL_HEADING(trail, i));
    }
    trail->point[31].angle = TRAIL_HEADING(trail, 30);
}

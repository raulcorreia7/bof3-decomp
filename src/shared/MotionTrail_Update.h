#include "area/effects.h"

u32 MATH_AverageAngle(u16 a, u16 b);

/* Link directions follow the nodes; the shifted offset keeps the trail pointer first in the add. */
#define MOTION_TRAIL_DIR(trail, i) (*(u16*)((u8*)(trail) + ((i) << 1) + sizeof((trail)->node)))

/* func_801F8D98 */
/* MotionTrail_Update (func_801F88B8 in scena07, func_801F8D98 in scena08, func_801F2F28 in area088): shifts the trail history, puts the task position first, projects every node to the screen and sets the node angles from the neighbour directions. Every change must verify every member. */
MATCH void MotionTrail_Update(void* table) {
    MotionTrail* trail;
    s8           i;
    s8           j;
    s32          prev;
    u16          size[2];
    u16          scale[2];
    MATRIX       camera;

    trail = table;
    for (i = 30; i >= 0; i--) {
        trail->node[i + 1] = trail->node[i];
    }
    trail->node[0].pos.vx = g_Task->pos.x.fixed;
    trail->node[0].pos.vy = g_Task->pos.y.fixed;
    trail->node[0].pos.vz = g_Task->pos.z.fixed;
    Area_SetCameraMatrix(&camera);
    for (i = 0; i < 32; i++) {
        Area_ProjectPoint(&trail->node[i].pos.vx, &trail->node[i].screen);
        size[0] = size[1] = trail->size;
        Game_ProjectWorldPoint(&trail->node[i], size, scale);
        trail->node[i].size = scale[0];
    }
    for (i = 0; i < 31; i++) {
        scale[0] = trail->node[i].screen.vx - trail->node[i + 1].screen.vx;
        scale[1] = trail->node[i].screen.vy - trail->node[i + 1].screen.vy;
        if ((s16)scale[0] != 0 || (s16)scale[1] != 0) {
            MOTION_TRAIL_DIR(trail, i) = ratan2((s16)scale[1], (s16)scale[0]);
        } else {
            MOTION_TRAIL_DIR(trail, i) = 0x1000;
        }
    }
    for (i = 0; i < 31; i++) {
        if (MOTION_TRAIL_DIR(trail, i) != 0x1000) {
            continue;
        }
        for (j = i + 1; j < 31; j++) {
            if (MOTION_TRAIL_DIR(trail, j) != 0x1000) {
                MOTION_TRAIL_DIR(trail, i) = MOTION_TRAIL_DIR(trail, j);
                goto next;
            }
        }
        for (j = 0; j < i; j++) {
            if (MOTION_TRAIL_DIR(trail, j) != 0x1000) {
                MOTION_TRAIL_DIR(trail, i) = MOTION_TRAIL_DIR(trail, j);
                goto next;
            }
        }
        MOTION_TRAIL_DIR(trail, j) = 0;
    next:;
    }
    trail->node[0].angle = MOTION_TRAIL_DIR(trail, 0);
    for (i = 1; i < 31; i++) {
        prev                 = i - 1;
        trail->node[i].angle = MATH_AverageAngle(MOTION_TRAIL_DIR(trail, prev), MOTION_TRAIL_DIR(trail, i));
    }
    trail->node[31].angle = MOTION_TRAIL_DIR(trail, 30);
}

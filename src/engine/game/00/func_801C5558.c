#include "game_00.h"

/* Route movement step table in main-exe data: one 8-byte record per route
 * {x step, y step}; the y column also appears as its own symbol. */

/* Per-route walk-completion threshold table in main-exe data, indexed by the
 * current map's route byte in the shared scenario state block at
 * g_Game.current+0x79. */

/* Per-route walk-completion threshold table, indexed by the current map's
 * route byte in the shared scenario state block at g_Game.current+0x79. */

MATCH void func_801C5558(void) {
    Actor* work;
    u16    count;
    u8     route;
    s32    step;
    s32    offs_x;
    s32    offs_y;
    s32    result;
    s16    threshold;

    work                   = g_Task;
    count                  = COORD_INT(work->pos.z) + 16;
    route                  = work->direction_08;
    COORD_INT(work->pos.z) = count;

    work   = g_Task;
    step   = work->state_70.byte + 2;
    /* FAKE: non-const view of the step table on the first read keeps retail's store order. */
    offs_x = (*(Point2l(*)[8])g_FacingSteps)[route].x * step;
    offs_y = g_FacingSteps[route].y * step;
    result = Area_ReadHeight(work->pos.x.fixed + offs_x, work->pos.y.fixed + offs_y);

    threshold = D_80181B70[g_Game.current->chr.character_id];

    work = g_Task;
    if ((s16)COORD_INT(work->pos.z) >= result - threshold) {
        work->header.step = 3;
    }

    Actor_StepAnimLoop();
}

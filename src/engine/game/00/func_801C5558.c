#include "game_00.h"

/* Route movement step table in main-exe data: one 8-byte record per route
 * {x step, y step}; the y column also appears as its own symbol. */

/* Per-route walk-completion threshold table in main-exe data, indexed by the
 * current map's route byte in the shared scenario state block at
 * g_GameState+0x79. */

/* Per-route walk-completion threshold table, indexed by the current map's
 * route byte in the shared scenario state block at g_GameState+0x79. */

MATCH void func_801C5558(void) {
    Actor* work;
    u16    count;
    u8     route;
    s32    step;
    s32    offs_x;
    s32    offs_y;
    s32    result;
    s16    threshold;

    work                 = g_SpadWork;
    count                = work->z.part.integer + 16;
    route                = work->direction_08;
    work->z.part.integer = count;

    work   = g_SpadWork;
    step   = work->state_70.byte + 2;
    /* FAKE: non-const view of the step table on the first read keeps retail's store order. */
    offs_x = (*(FacingStep(*)[8])g_FacingSteps)[route].x * step;
    offs_y = g_FacingSteps[route].y * step;
    result = Area_ReadHeight(work->x.fixed + offs_x, work->y.fixed + offs_y);

    threshold = D_80181B70[g_GameState->slot_index_79];

    work = g_SpadWork;
    if ((s16)work->z.part.integer >= result - threshold) {
        work->state_02 = 3;
    }

    func_8014D978();
}

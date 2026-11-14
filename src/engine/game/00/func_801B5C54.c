#include "game_00.h"

MATCH void* func_801B5C54(void) {
    Actor*      work;
    TileRuns* entry;
    TileRun*    run;
    TileRun*    cur;
    s32         index;
    s32         sub;
    s32         limit;
    s32         step;
    s32         pos;
    s32         x;
    s32         y;
    s32         origin;
    s8          delta;

    entry = GAME_TILE_RUN(g_GameAreaId);
    index = entry->last_run;
    run   = entry->runs;
    if (index < 0)
        return NULL;
    work = g_Task;
    /* Spelled run - -index: retail adds the scaled index before the base (&run[index] swaps the addu). */
    cur  = run - -index;
    for (; index >= 0; index--, cur--) {
        sub = cur->len - 1;
        run = cur;
        for (; sub >= 0; sub--) {
            if (work->state_70.byte == 0) {
                limit = 1;
                pos   = work->direction_08 * 2;
                /* FAKE: volatile u8 reads keep retail's lbu + sll/sra pair; an s8 read folds to lb (63.57%). */
                x     = (u16)COORD_INT(work->pos.x) + (s8)((volatile u8*)D_80181B00)[pos];
                y     = (u16)COORD_INT(work->pos.y) + (s8)((volatile u8*)D_80181B01)[pos];
                if (COORD_FRAC(work->pos.x) == 0)
                    limit = (COORD_FRAC(work->pos.y) != 0);
            } else {
                delta  = D_80181B00[work->direction_08 * 2];
                origin = COORD_INT(work->pos.x);
                if (delta == 1)
                    x = origin + 2;
                else
                    x = origin + delta;
                delta  = D_80181B01[work->direction_08 * 2];
                origin = COORD_INT(work->pos.y);
                if (delta == 1)
                    y = origin + 2;
                else
                    y = origin + delta;
                if ((work->direction_08 == FACING_UP) || (work->direction_08 == FACING_DOWN))
                    limit = (COORD_FRAC(work->pos.x) != 0);
                else
                    limit = (COORD_FRAC(work->pos.y) != 0);
            }
            for (step = 0; step <= limit; step++) {
                if (((run->flags & TILE_RUN_VERTICAL) && (x & BYTE_MASK) == run->x && (y & BYTE_MASK) == run->y + sub) ||
                    (!(run->flags & TILE_RUN_VERTICAL) && (x & BYTE_MASK) == run->x + sub && (y & BYTE_MASK) == run->y))
                    return run;
                if ((work->direction_08 == FACING_UP) || (work->direction_08 == FACING_DOWN))
                    x += 1;
                else
                    y += 1;
            }
        }
    }
    return NULL;
}

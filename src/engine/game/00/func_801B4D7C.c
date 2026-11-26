#include "game_00.h"

/* Turns the work actor towards a neighbouring cell carrying the wanted code. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801B4D7C(u8 wanted_code) {
    s8  delta;
    s32 x;
    s32 y;
    s32 i;

    if ((TASK(Actor)->pos.x.part.fraction == 0) && (TASK(Actor)->pos.y.part.fraction == 0)) {
        return 0;
    }
    delta = D_80181B00[TASK(Actor)->direction * 2];
    x     = TASK(Actor)->pos.x.part.integer + ((delta == 1) ? 2 : delta);
    delta = D_80181B01[TASK(Actor)->direction * 2];
    y     = TASK(Actor)->pos.y.part.integer + ((delta == 1) ? 2 : delta);

    i = 0;
    if ((TASK(Actor)->pos.x.part.fraction != 0) && (TASK(Actor)->pos.y.part.fraction != 0)) {
        g_ScratchPad.cells.halves[0] = TASK(Actor)->pos.x.part.integer;
        D_1F800002                   = y;
        for (; i < 2; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                if (TASK(Actor)->direction & 1) {
                    if ((TASK(Actor)->direction == FACING_UP) || (TASK(Actor)->direction == FACING_DOWN)) {
                        return 1;
                    }
                } else {
                    if ((TASK(Actor)->direction == FACING_UP_LEFT) || (TASK(Actor)->direction == FACING_UP_RIGHT)) {
                        TASK(Actor)->direction = FACING_UP;
                    } else {
                        TASK(Actor)->direction = FACING_DOWN;
                    }
                    return 1;
                }
            }
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] + 1;
        }
        i                            = 0;
        g_ScratchPad.cells.halves[0] = x;
        D_1F800002                   = TASK(Actor)->pos.y.part.integer;
        for (; i < 2; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                if (TASK(Actor)->direction & 1) {
                    if ((TASK(Actor)->direction == FACING_LEFT) || (TASK(Actor)->direction == FACING_RIGHT)) {
                        return 1;
                    }
                } else {
                    if ((TASK(Actor)->direction == FACING_UP_LEFT) || (TASK(Actor)->direction == FACING_DOWN_LEFT)) {
                        TASK(Actor)->direction = FACING_LEFT;
                    } else {
                        TASK(Actor)->direction = FACING_RIGHT;
                    }
                    return 1;
                }
            }
            g_ScratchPad.cells.ray.y = g_ScratchPad.cells.ray.y + 1;
        }
        if (!func_801B4BE4((TASK(Actor)->direction + 2) & 7, wanted_code) && !func_801B4BE4((TASK(Actor)->direction - 2) & 7, wanted_code)) {
            return 0;
        }
        return 1;
    } else if (TASK(Actor)->pos.x.part.fraction == 0) {
        g_ScratchPad.cells.halves[0] = TASK(Actor)->pos.x.part.integer - 1;
        D_1F800002                   = y;
        for (; i < 3; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                if (TASK(Actor)->direction & 1) {
                    if ((TASK(Actor)->direction == FACING_UP) || (TASK(Actor)->direction == FACING_DOWN)) {
                        return 1;
                    }
                } else {
                    if ((TASK(Actor)->direction == FACING_UP_LEFT) || (TASK(Actor)->direction == FACING_UP_RIGHT)) {
                        TASK(Actor)->direction = FACING_UP;
                    } else {
                        TASK(Actor)->direction = FACING_DOWN;
                    }
                    return 1;
                }
            }
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] + 1;
        }
        if ((TASK(Actor)->direction == FACING_LEFT) || (TASK(Actor)->direction == FACING_RIGHT)) {
        i                            = 0;
        g_ScratchPad.cells.halves[0] = TASK(Actor)->pos.x.part.integer - 1;
        D_1F800002                   = TASK(Actor)->pos.y.part.integer - 1;
        for (; i < 3; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                TASK(Actor)->direction = FACING_UP;
                return 1;
            }
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] + 1;
        }
        i                            = 0;
        g_ScratchPad.cells.halves[0] = TASK(Actor)->pos.x.part.integer - 1;
        D_1F800002                   = TASK(Actor)->pos.y.part.integer + 2;
        for (; i < 3; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                TASK(Actor)->direction = FACING_DOWN;
                return 1;
            }
            g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[0] + 1;
        }
        }
        return 0;
    } else {
        g_ScratchPad.cells.halves[0] = x;
        D_1F800002                   = TASK(Actor)->pos.y.part.integer - 1;
        for (; i < 3; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                if (TASK(Actor)->direction & 1) {
                    if (TASK(Actor)->direction == FACING_LEFT) {
                        return 1;
                    }
                    if (TASK(Actor)->direction == FACING_RIGHT) {
                        return 1;
                    }
                } else {
                    if ((TASK(Actor)->direction == FACING_UP_LEFT) || (TASK(Actor)->direction == FACING_DOWN_LEFT)) {
                        TASK(Actor)->direction = FACING_LEFT;
                    } else {
                        TASK(Actor)->direction = FACING_RIGHT;
                    }
                    return 1;
                }
            }
            g_ScratchPad.cells.ray.y = g_ScratchPad.cells.ray.y + 1;
        }
        if ((TASK(Actor)->direction == FACING_UP) || (TASK(Actor)->direction == FACING_DOWN)) {
        i                            = 0;
        g_ScratchPad.cells.halves[0] = TASK(Actor)->pos.x.part.integer - 1;
        D_1F800002                   = TASK(Actor)->pos.y.part.integer - 1;
        for (; i < 3; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                TASK(Actor)->direction = FACING_LEFT;
                return 1;
            }
            g_ScratchPad.cells.halves[1] = g_ScratchPad.cells.halves[1] + 1;
        }
        i                            = 0;
        g_ScratchPad.cells.halves[0] = TASK(Actor)->pos.x.part.integer + 2;
        D_1F800002                   = TASK(Actor)->pos.y.part.integer - 1;
        for (; i < 3; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                TASK(Actor)->direction = FACING_RIGHT;
                return 1;
            }
            g_ScratchPad.cells.halves[1] = g_ScratchPad.cells.halves[1] + 1;
        }
        }
        return 0;
    }
}
#else
INCLUDE_ASM(func_801B4D7C);
#endif

#include "game_00.h"

/* Whether a cell beside the actor's step holds wanted_code; turns a diagonal facing onto it. */
MATCH u8 func_801B44DC(u8 wanted_code) {
    s32 i;
    u8  dir;
    s16 x;
    s16 y;

    if (COORD_FRAC(SELF(Actor)->pos.x) != 0 && COORD_FRAC(SELF(Actor)->pos.y) != 0)
        return false;
    dir = SELF(Actor)->direction;
    x   = COORD_INT(SELF(Actor)->pos.x) + D_80181B00[dir][0];
    y   = COORD_INT(SELF(Actor)->pos.y) + D_80181B00[dir][1];
    if (COORD_FRAC(SELF(Actor)->pos.x) == 0 && COORD_FRAC(SELF(Actor)->pos.y) == 0) {
        g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x);
        g_ScratchPad.cells.halves[1] = y;
        if ((Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), y) & BYTE_MASK) == wanted_code) {
            g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x);
            g_ScratchPad.cells.halves[1] = y;
            dir                          = SELF(Actor)->direction;
            if (dir & 1) {
                if (dir == FACING_UP || dir == FACING_DOWN)
                    return true;
            } else {
                SELF(Actor)->direction = (dir == FACING_UP_LEFT || dir == FACING_UP_RIGHT) ? FACING_UP : FACING_DOWN;
                return true;
            }
        } else if ((Area_CellGetCode(x, COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK) == wanted_code) {
            g_ScratchPad.cells.halves[0] = x;
            g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y);
            dir                          = SELF(Actor)->direction;
            if (dir & 1) {
                if (dir == FACING_LEFT || dir == FACING_RIGHT)
                    return true;
            } else {
                SELF(Actor)->direction = (dir == FACING_UP_LEFT || dir == FACING_DOWN_LEFT) ? FACING_LEFT : FACING_RIGHT;
                return true;
            }
        } else if (SELF(Actor)->direction & 1) {
            i                            = (SELF(Actor)->direction + 2) & 7;
            g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x) + D_80181B00[i][0];
            g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y) + D_80181B00[i][1];
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) != wanted_code) {
                i                            = (SELF(Actor)->direction - 2) & 7;
                g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x) + D_80181B00[i][0];
                g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y) + D_80181B00[i][1];
                if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) != wanted_code)
                    return false;
            }
            SELF(Actor)->direction = i;
            return true;
        }
        return false;
    }
    if (COORD_FRAC(SELF(Actor)->pos.x) != 0) {
        if (dir != FACING_LEFT && dir != FACING_RIGHT) {
            g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x);
            g_ScratchPad.cells.halves[1] = y;
            for (i = 0; i < 2; i++) {
                if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                    dir = SELF(Actor)->direction;
                    if (dir & 1) {
                        if (dir == FACING_UP || dir == FACING_DOWN)
                            return true;
                    } else {
                        if (dir == FACING_UP_LEFT || dir == FACING_UP_RIGHT)
                            SELF(Actor)->direction = FACING_UP;
                        else
                            SELF(Actor)->direction = FACING_DOWN;
                        return true;
                    }
                }
                g_ScratchPad.cells.halves[0]++;
            }
            return false;
        }
        g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x);
        g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y) - 1;
        for (i = 0; i < 2; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                SELF(Actor)->direction = FACING_UP;
                return true;
            }
            g_ScratchPad.cells.halves[0]++;
        }
        g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x);
        g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y) + 1;
        for (i = 0; i < 2; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                SELF(Actor)->direction = FACING_DOWN;
                return true;
            }
            g_ScratchPad.cells.halves[0]++;
        }
        return false;
    }
    if (dir != FACING_UP && dir != FACING_DOWN) {
        g_ScratchPad.cells.halves[0] = x;
        g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y);
        for (i = 0; i < 2; i++) {
            if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
                dir = SELF(Actor)->direction;
                if (dir & 1) {
                    if (dir == FACING_LEFT || dir == FACING_RIGHT)
                        return true;
                } else {
                    if (dir == FACING_UP_LEFT || dir == FACING_DOWN_LEFT)
                        SELF(Actor)->direction = FACING_LEFT;
                    else
                        SELF(Actor)->direction = FACING_RIGHT;
                    return true;
                }
            }
            g_ScratchPad.cells.halves[1]++;
        }
        return false;
    }
    g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x) - 1;
    g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y);
    for (i = 0; i < 2; i++) {
        if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
            SELF(Actor)->direction = FACING_LEFT;
            return true;
        }
        g_ScratchPad.cells.halves[1]++;
    }
    g_ScratchPad.cells.halves[0] = COORD_INT(SELF(Actor)->pos.x) + 1;
    g_ScratchPad.cells.halves[1] = COORD_INT(SELF(Actor)->pos.y);
    for (i = 0; i < 2; i++) {
        if ((Area_CellGetCode(g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1]) & BYTE_MASK) == wanted_code) {
            SELF(Actor)->direction = FACING_RIGHT;
            return true;
        }
        g_ScratchPad.cells.halves[1]++;
    }
    return false;
}

#include "game_00.h"

/* Scratch byte 0: nonzero while the current route probe is active. The retail
 * code materializes this symbol address in each branch, so FAKE_VOLATILE keeps the
 * pointer expression rather than a cached direct access. */

MATCH bool func_801B8D18(void) {
    s16 value;
    s32 x;
    s32 y;

    if (TASK(Actor)->voice_flags.scene_flag == 0) {
        if (TASK(Actor)->direction == FACING_RIGHT) {
            if (COORD_FRAC(TASK(Actor)->pos.x) != 0) {
                return false;
            }
            x     = TASK(Actor)->pos.x.fixed + COORD_HALF;
            y     = TASK(Actor)->pos.y.fixed & 0xFFFF0000;
            value = Area_HeightReadStep(x, y, 3);
            if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
                return false;
            }
            if (COORD_FRAC(TASK(Actor)->pos.y) != 0) {
                value = Area_HeightReadStep(x, y + 0x8000, 3);
                if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
                    return false;
                }
            }
            return true;
        }
        if (TASK(Actor)->direction == FACING_DOWN) {
            if (COORD_FRAC(TASK(Actor)->pos.y) != 0) {
                return false;
            }
            x     = TASK(Actor)->pos.x.fixed & 0xFFFF0000;
            y     = TASK(Actor)->pos.y.fixed + COORD_HALF;
            value = Area_HeightReadStep(x, y, 5);
            if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
                return false;
            }
            if (COORD_FRAC(TASK(Actor)->pos.x) != 0) {
                value = Area_HeightReadStep(x + 0x8000, y, 5);
                if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    if (TASK(Actor)->direction == FACING_RIGHT) {
        if (COORD_FRAC(TASK(Actor)->pos.x) == 0) {
            return false;
        }
        x     = TASK(Actor)->pos.x.fixed + TO_COORD(1);
        y     = TASK(Actor)->pos.y.fixed & 0xFFFF0000;
        value = Area_HeightReadStep(x, y, 3);
        if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
            return false;
        }
        y |= 32768;
        value = Area_HeightReadStep(x, y, 3);
        if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
            return false;
        }
        if (COORD_FRAC(TASK(Actor)->pos.y) == 0) {
            value = Area_HeightReadStep(x, y - TO_COORD(1), 3);
            if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
                return false;
            }
        }
        return true;
    }
    if (TASK(Actor)->direction == FACING_DOWN) {
        if (COORD_FRAC(TASK(Actor)->pos.y) == 0) {
            return false;
        }
        x     = TASK(Actor)->pos.x.fixed & 0xFFFF0000;
        y     = TASK(Actor)->pos.y.fixed + TO_COORD(1);
        value = Area_HeightReadStep(x, y, 5);
        if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
            return false;
        }
        x |= 32768;
        value = Area_HeightReadStep(x, y, 5);
        if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
            return false;
        }
        if (COORD_FRAC(TASK(Actor)->pos.x) == 0) {
            value = Area_HeightReadStep(x - TO_COORD(1), y, 3);
            if (g_ScratchPad.cells.bytes[0] == 0 || value < 0x41) {
                return false;
            }
        }
        return true;
    }
    return false;
}

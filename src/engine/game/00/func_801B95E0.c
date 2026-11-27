#include "game_00.h"

#define STEP_TILE_X(n) ((((s16)SELF(Actor)->pos.x.part.integer + (n)) << 0x10) >> 1)
#define PAD_FLAG       SP_REF(u8, 0x0)
#define PAD_A          SP_REF(u8, 0x8)
#define PAD_B          SP_REF(u8, 0x9)
#define PAD_C          SP_REF(u8, 0xA)
#define WDIR           SELF(Actor)->direction

MATCH s32 func_801B95E0(void) {
    s16 x;
    s16 y;
    s16 y_arg;
    u8  dir;
    s16 height;
    /* FAKE: retail's frame leaves sp+16..47 unused, between the argument area and the saved registers. */
    FAKE_STACK_PADS(s32, 8);

    if (g_Game.flags & 0x400) {
        return 1;
    }
    dir = WDIR;
    if (COORD_FRAC(SELF(Actor)->pos.x) != 0 && COORD_FRAC(SELF(Actor)->pos.y) != 0) {
        return 1;
    }
    x     = SELF(Actor)->pos.x.part.integer + (s8)D_80181B00[WDIR][0];
    y_arg = y = SELF(Actor)->pos.y.part.integer + (s8)D_80181B00[WDIR][1];
    Area_WalkProbeCells(x, y_arg);

    if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
        if (COORD_FRAC(SELF(Actor)->pos.x) == 0) {
            if (COORD_FRAC(SELF(Actor)->pos.y) == 0) {
                g_ScratchPad.cells.bytes[8] = func_801B9F08(1, 2, 3);
                g_ScratchPad.cells.bytes[9] = func_801B9F08(2, 0, 0);
                PAD_C                       = func_801B9F08(3, 0, 0);
                if (g_ScratchPad.cells.bytes[8] == 0xB0) {
                    return 6;
                }
                {
                    if (g_ScratchPad.cells.bytes[8] == 0x10 || g_ScratchPad.cells.bytes[8] == 0x20) {
                        if ((g_ScratchPad.cells.words[2] & 0xFFFF00) == 0x101000) {
                            return 0;
                        }
                        if (g_ScratchPad.cells.bytes[9] == 0x10) {
                            Actor_SnapFacing(2, 4, 3);
                        } else if (PAD_C == 0x10) {
                            Actor_SnapFacing(4, 6, 5);
                        } else {
                            SELF(Actor)->direction = (WDIR + 1) & 7;
                        }
                    }
                    if (!(g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP)) {
                        if ((PAD_B & 0xF0) == 0xA0 && (WDIR == 1 || WDIR == 5)) {
                            return func_801BB7B0(9) & BYTE_MASK;
                        }
                        if ((PAD_C & 0xF0) == 0xA0 && (WDIR == 3 || WDIR == 7)) {
                            return func_801BB7B0(0xA) & BYTE_MASK;
                        }
                        if ((PAD_B & 0xF0) == 0xA0) {
                            WDIR = dir;
                            Actor_SnapFacing(4, 6, 5);
                            return func_801BB7B0(9) & BYTE_MASK;
                        }
                        if ((PAD_C & 0xF0) == 0xA0) {
                            WDIR = dir;
                            Actor_SnapFacing(2, 4, 3);
                            return func_801BB7B0(0xA) & BYTE_MASK;
                        }
                    }
                    if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
                        height = Area_HeightReadStep(STEP_TILE_X(x), y << 0x10, 3);
                        if (PAD_FLAG != 0 && height >= 0x41) {
                            Actor_SnapFacing(4, 6, 5);
                            return 1;
                        }
                        if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
                            height = Area_HeightReadStep(x << 0x10, (((s16)SELF(Actor)->pos.y.part.integer + y) << 0x10) >> 1, 1);
                            if (PAD_FLAG != 0 && height >= 0x41) {
                                Actor_SnapFacing(2, 4, 3);
                                return 1;
                            }
                        }
                    }
                    return 3;
                }
            }
            goto north_south;
        }
        if (COORD_FRAC(SELF(Actor)->pos.y) == 0) {
            PAD_A = func_801B9F08(2, 4, 0);
            if (PAD_A == 0x70) {
                Actor_SnapFacing(4, 6, 5);
                return 7;
            }
            if (PAD_A == 0x10 || PAD_A == 0x20) {
                Actor_SnapFacing(2, 4, 3);
            }
            if ((PAD_A & 0xF0) != 0xA0) {
                return 3;
            }
            if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
                Actor_SnapFacing(4, 6, 5);
            }
            return func_801BB7B0(8) & BYTE_MASK;
        }
    north_south:
        PAD_A = func_801B9F08(3, 5, 0);
        if (PAD_A == 0x70) {
            Actor_SnapFacing(2, 4, 3);
            return 7;
        }
        if (PAD_A == 0xB0) {
            return 6;
        }
        if (PAD_A == 0x10 || PAD_A == 0x20) {
            Actor_SnapFacing(4, 6, 5);
        }
        if ((PAD_A & 0xF0) != 0xA0) {
            return 3;
        }
        if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
            Actor_SnapFacing(2, 4, 3);
        }
        return func_801BB7B0(8) & BYTE_MASK;
    }

    if (COORD_FRAC(SELF(Actor)->pos.x) == 0) {
        if (COORD_FRAC(SELF(Actor)->pos.y) == 0) {
            PAD_A = func_801B9F08(1, 0, 0);
            if (PAD_A == 0xB0) {
                return 6;
            }
            if (PAD_A == 0x10) {
                return 0;
            }
            if ((PAD_A & 0xF0) != 0xA0) {
                return 3;
            }
            return func_801BB7B0(8) & BYTE_MASK;
        }
        goto diag_south;
    }
    if (COORD_FRAC(SELF(Actor)->pos.y) == 0) {
        if (SELF(Actor)->direction & 2) {
            return 3;
        }
        PAD_A = func_801B9F08(2, 4, 0);
        if (PAD_A == 0xB0) {
            return 6;
        }
        if (PAD_A == 0x70) {
            return 7;
        }
        if (PAD_A == 0x20) {
            return 0;
        }
        if (PAD_A == 0x10) {
            if (func_801BB934(2, 4, 3, 0xFF) & BYTE_MASK) {
                return 0;
            }
            if (func_801BB934(2, 4, 3, 0x70) & BYTE_MASK) {
                return 0;
            }
            if (func_801BB934(2, 4, 7, 0xA0) & BYTE_MASK) {
                return 0;
            }
            if (func_801BB934(2, 4, 7, 0xA1) & BYTE_MASK) {
                return 0;
            }
            if (func_801BB934(2, 4, 7, 0xA2) & BYTE_MASK) {
                return 0;
            }
            return (func_801BB934(2, 4, 7, 0xA3) & BYTE_MASK) == 0;
        }
        if ((PAD_A & 0xF0) == 0xA0) {
            return func_801BB7B0(8) & BYTE_MASK;
        }
        height = Area_HeightReadStep(((((s16)SELF(Actor)->pos.x.part.integer * 2) + 1) << 0x10) >> 1, y_arg << 0x10, 1);
        if (PAD_FLAG != 0 && height >= 0x41) {
            WDIR = 7;
            return 1;
        }
        return 3;
    }
diag_south:
    if (!(WDIR & 2)) {
        return 3;
    }
    PAD_A = func_801B9F08(3, 5, 0);
    if (PAD_A == 0xB0) {
        return 6;
    }
    if (PAD_A == 0x70) {
        return 7;
    }
    if (PAD_A == 0x20) {
        return 0;
    }
    if (PAD_A == 0x10) {
        if (func_801BB934(3, 5, 5, 0xFF) & BYTE_MASK) {
            return 0;
        }
        if (func_801BB934(3, 5, 5, 0x70) & BYTE_MASK) {
            return 0;
        }
        if (func_801BB934(3, 5, 1, 0xA0) & BYTE_MASK) {
            return 0;
        }
        if (func_801BB934(3, 5, 1, 0xA1) & BYTE_MASK) {
            return 0;
        }
        if (func_801BB934(3, 5, 1, 0xA2) & BYTE_MASK) {
            return 0;
        }
        return -((func_801BB934(3, 5, 1, 0xA3) & BYTE_MASK) == 0) & 3;
    }
    if ((PAD_A & 0xF0) == 0xA0) {
        return func_801BB7B0(8) & BYTE_MASK;
    }
    height = Area_HeightReadStep(x << 0x10, ((((s16)SELF(Actor)->pos.y.part.integer * 2) + 1) << 0x10) >> 1, 1);
    if (PAD_FLAG != 0 && height >= 0x41) {
        WDIR = 1;
        return 1;
    }
    return 3;
}

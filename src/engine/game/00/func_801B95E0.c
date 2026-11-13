#include "game_00.h"

#define STEP_TILE_X(n) ((((s16)FIELD(u16, g_Task, 0x36u) + (n)) << 0x10) >> 1)
#define PAD_FLAG       SP_REF(u8, 0x0)
#define PAD_A          SP_REF(u8, 0x8)
#define PAD_B          SP_REF(u8, 0x9)
#define PAD_C          SP_REF(u8, 0xA)
#define WDIR           g_Task->direction_08

#ifdef NON_MATCHING
NON_MATCHING s32 func_801B95E0(void) {
    s16 x;
    s16 y;
    s16 y_arg;
    u8  dir;
    s32 probe;
    u8* pad;
    s32 v;
    s32 ret;
    /* FAKE: retail's frame is 8 bytes larger than the statements need. */
    FAKE_STACK_PADS(s32, 8);

    if (g_Game.flags & 0x400) {
        return 1;
    }
    dir = WDIR;
    if (COORD_FRAC(g_Task->pos.x) != 0 && COORD_FRAC(g_Task->pos.y) != 0) {
        return 1;
    }
    x     = FIELD(u16, g_Task, 0x36u) + (s8)D_80181B00[WDIR * 2];
    y_arg = y = FIELD(u16, g_Task, 0x3Au) + (s8)D_80181B01[WDIR * 2];
    func_801BBBC8(x, y_arg);

    if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
        if (COORD_FRAC(g_Task->pos.x) == 0) {
            if (COORD_FRAC(g_Task->pos.y) == 0) {
                pad    = (u8*)&D_1F800008;
                pad[0] = func_801B9F08(1, 2, 3);
                pad[1] = func_801B9F08(2, 0, 0);
                PAD_C  = func_801B9F08(3, 0, 0);
                if (pad[0] == 0xB0) {
                    return 6;
                }
                {
                    if (pad[0] == 0x10 || pad[0] == 0x20) {
                        if ((*(u32*)pad & 0xFFFF00) == 0x101000) {
                            return 0;
                        }
                        if (pad[1] == 0x10) {
                            func_801BB8E8(2, 4, 3);
                        } else if (PAD_C == 0x10) {
                            func_801BB8E8(4, 6, 5);
                        } else {
                            g_Task->direction_08 = (WDIR + 1) & 7;
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
                            func_801BB8E8(4, 6, 5);
                            return func_801BB7B0(9) & BYTE_MASK;
                        }
                        if ((PAD_C & 0xF0) == 0xA0) {
                            WDIR = dir;
                            func_801BB8E8(2, 4, 3);
                            return func_801BB7B0(0xA) & BYTE_MASK;
                        }
                    }
                    ret = 3;
                    if (WDIR & AREA_LOAD_FLAG_WORLD_MAP) {
                        return ret;
                    }
                    probe = Area_ReadStepHeight(STEP_TILE_X(x), y << 0x10, 3) << 0x10;
                    if (PAD_FLAG != 0 && (probe >> 0x10) >= 0x41) {
                        func_801BB8E8(4, 6, 5);
                        return 1;
                    }
                    ret = 3;
                    if (WDIR & AREA_LOAD_FLAG_WORLD_MAP) {
                        return ret;
                    }
                    probe = Area_ReadStepHeight(x << 0x10, (((s16)FIELD(u16, g_Task, 0x3Au) + y) << 0x10) >> 1, 1) << 0x10;
                    if (PAD_FLAG == 0) {
                        return 3;
                    }
                    if ((probe >> 0x10) < 0x41) {
                        return ret;
                    }
                    func_801BB8E8(2, 4, 3);
                    return 1;
                }
            }
            goto north_south;
        }
        if (COORD_FRAC(g_Task->pos.y) == 0) {
            v     = func_801B9F08(2, 4, 0);
            PAD_A = v;
            if (v == 0x70) {
                func_801BB8E8(4, 6, 5);
                return 7;
            }
            if (v == 0x10 || v == 0x20) {
                func_801BB8E8(2, 4, 3);
            }
            if ((PAD_A & 0xF0) != 0xA0) {
                return 3;
            }
            if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
                func_801BB8E8(4, 6, 5);
            }
            return func_801BB7B0(8) & BYTE_MASK;
        }
    north_south:
        v     = func_801B9F08(3, 5, 0);
        PAD_A = v;
        if (v == 0x70) {
            func_801BB8E8(2, 4, 3);
            return 7;
        }
        if (v == 0xB0) {
            return 6;
        }
        if (v == 0x10 || v == 0x20) {
            func_801BB8E8(4, 6, 5);
        }
        if ((PAD_A & 0xF0) != 0xA0) {
            return 3;
        }
        if (!(WDIR & AREA_LOAD_FLAG_WORLD_MAP)) {
            func_801BB8E8(2, 4, 3);
        }
        return func_801BB7B0(8) & BYTE_MASK;
    }

    if (COORD_FRAC(g_Task->pos.x) == 0) {
        if (COORD_FRAC(g_Task->pos.y) == 0) {
            v     = func_801B9F08(1, 0, 0);
            PAD_A = v;
            if (v == 0xB0) {
                return 6;
            }
            if (v == 0x10) {
                return 0;
            }
            if ((v & 0xF0) == 0xA0) {
                return func_801BB7B0(8) & BYTE_MASK;
            }
            return 3;
        }
        goto diag_south;
    }
    if (COORD_FRAC(g_Task->pos.y) == 0) {
        if (g_Task->direction_08 & 2) {
            return 3;
        }
        v     = func_801B9F08(2, 4, 0);
        PAD_A = v;
        if (v == 0xB0) {
            return 6;
        }
        if (v == 0x70) {
            return 7;
        }
        if (v == 0x20) {
            return 0;
        }
        if (v == 0x10) {
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
        if ((v & 0xF0) == 0xA0) {
            return func_801BB7B0(8) & BYTE_MASK;
        }
        probe = Area_ReadStepHeight(((((s16)FIELD(u16, g_Task, 0x36u) * 2) + 1) << 0x10) >> 1, y_arg << 0x10, 1) << 0x10;
        if (PAD_FLAG != 0) {
            ret = 3;
            if ((probe >> 0x10) >= 0x41) {
                WDIR = 7;
                return 1;
            }
            return ret;
        }
        return 3;
    }
diag_south:
    if (!(WDIR & 2)) {
        return 3;
    }
    v     = func_801B9F08(3, 5, 0);
    PAD_A = v;
    if (v == 0xB0) {
        return 6;
    }
    if (v == 0x70) {
        return 7;
    }
    if (v == 0x20) {
        return 0;
    }
    if (v == 0x10) {
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
    if ((v & 0xF0) == 0xA0) {
        return func_801BB7B0(8) & BYTE_MASK;
    }
    probe = Area_ReadStepHeight(x << 0x10, ((((s16)FIELD(u16, g_Task, 0x3Au) * 2) + 1) << 0x10) >> 1, 1) << 0x10;
    if (PAD_FLAG != 0) {
        ret = 3;
        if ((probe >> 0x10) >= 0x41) {
            WDIR = 1;
            return 1;
        }
        return ret;
    }
    return 3;
}
#else
INCLUDE_ASM(func_801B95E0);
#endif

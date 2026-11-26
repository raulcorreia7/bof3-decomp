#include "game_00.h"

/* A coordinate word whose high half is written alone; retail masks the uninitialized low half. */
typedef union {
    s32 w;

    struct {
        u16 lo;
        u16 hi;
    } h;
} GameCoordPack;

#ifdef NON_MATCHING
NON_MATCHING s32 func_801BB2B8(s32 x0, s32 y0, s32 x1, s32 y1) {
    s32           hx0;
    s32           hy0;
    GameCoordPack to_x;
    GameCoordPack to_y;
    s32           code1;
    s32           code2;
    s32           key;
    s32           bit;

    hx0       = x0 << 16;
    hy0       = y0 << 16;
    to_x.h.hi = x1;
    to_y.h.hi = y1;

    if (COORD_FRAC(TASK(Actor)->pos.x) == 0) {
        if (TASK(Actor)->voice_flags.scene_flag == 0)
            hx0 = (hx0 + (to_x.w & ~0xFFFFU)) / 2;
    } else if (TASK(Actor)->voice_flags.scene_flag != 0) {
        hx0 = (hx0 + (to_x.w & ~0xFFFFU)) / 2;
    }
    if (COORD_FRAC(TASK(Actor)->pos.y) == 0) {
        if (TASK(Actor)->voice_flags.scene_flag == 0)
            hy0 = (hy0 + (to_y.w & ~0xFFFFU)) / 2;
    } else if (TASK(Actor)->voice_flags.scene_flag != 0) {
        hy0 = (hy0 + (to_y.w & ~0xFFFFU)) / 2;
    }

    code1 = AREA_CELL_CODE_S16(x0, y0);
    code2 = AREA_CELL_CODE_S16(x1, y1);
    key   = code1 & 0xF0;

    switch (key) {
        case 0x80:
            if (TASK(Actor)->unk_05 != 0)
                return 0xFF;
        case 0x00:
        case 0x60:
        case 0x90:
        case 0xB0:
        case 0xC0:
        case 0xD0:
        case 0xE0:
            if ((u8)func_801BB6F0(code2 & 0xFF))
                return 0xB0;
            if ((u8)func_801BB760(hx0, hy0))
                return 0xFF;
            return code1 & 0xFF;
        case 0x10:
            if ((code1 & 0xFF) == 0x11) {
                if (g_Task == (void*)&D_8014626C)
                    bit = g_Game.unk_3E7 & 1;
                else
                    bit = g_GameState->status.field.flags.unsigned_value & 1;
                if (bit != 0)
                    return 0;
            }
        case 0x30:
        case 0x40:
        case 0x50:
            if ((code1 & 0xFF) == 0x52 && (u8)func_801BB760(hx0, hy0) == 0)
                return 0;
            return 0xFF;
        case 0x70:
            if ((code2 & 0xFF) == key && (u8)func_801BB760(hx0, hy0))
                return 0x70;
            break;
        case 0x20:
            if ((u8)func_801BB760(hx0, hy0))
                return 0xFF;
            if ((code2 & 0xF0) != key)
                return code1 & 0xF1;
            if ((code1 & 0xF1) != (code2 & 0xF1))
                return 0xFF;
            return code1 & 0xF1;
        case 0xA0:
            if ((code2 & 0xFF) == 0xC0) {
                if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
                    if ((code1 & 0xFF) == key || (code1 & 0xFF) == 0xAE)
                        return 0;
                }
                if ((code1 & 0xFF) == 0xAF)
                    return 0xA1;
                if (TASK(Actor)->unk_05 == 0)
                    return code1 & 0xFF;
                return 0xFF;
            }
            if ((code1 & 0xFF) == 0xA2)
                return 0xFF;
            if ((code1 & 0xFF) == 0xA3)
                return 0xFF;
            break;
        case 0xF0:
            return 0xFF;
        default:
            return code1 & 0xFF;
    }
    return (u8)func_801BB760(hx0, hy0) ? 0xFF : 0;
}
#else
INCLUDE_ASM(func_801BB2B8);
#endif

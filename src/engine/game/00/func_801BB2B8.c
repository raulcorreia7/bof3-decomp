#include "game_00.h"

/* Packed coordinate pair; the high half carries the shifted coordinate.
 * RESIDUAL: the original reads the (uninitialized) word's low half before
 * writing `hi` — retail's prologue `andi t0,t0,0xFFFF; or t0,t0,(x1<<16);
 * and t0,t0,0xFFFF0000` is exactly this field insert + word mask on an
 * uninitialized local, so the union word must stay uninitialized here.
 */
typedef union {
    s32 w;

    struct {
        u16 lo;
        u16 hi;
    } h;
} GameCoordPack;

#ifdef NON_MATCHING
NON_MATCHING s32 func_801BB2B8(s32 x0, s32 y0, s32 x1, s32 y1) {
    Actor*        work;
    s32           hx0;
    s32           hy0;
    GameCoordPack xpack;
    GameCoordPack ypack;
    s32           code1;
    s32           code2;
    s32           key;
    s32           low;
    s32           bit;
    hx0        = x0 << 16;
    hy0        = y0 << 16;
    xpack.h.hi = x1;
    ypack.h.hi = y1;
    work       = g_Task;

    if (COORD_FRAC(work->pos.x) == 0) {
        if (work->state_70.byte == 0)
            hx0 = (hx0 + (xpack.w & -0x10000)) / 2;
    } else if (work->state_70.byte != 0) {
        hx0 = (hx0 + (xpack.w & -0x10000)) / 2;
    }

    work = g_Task;
    if (COORD_FRAC(work->pos.y) == 0) {
        if (work->state_70.byte == 0)
            hy0 = (hy0 + (ypack.w & -0x10000)) / 2;
    } else if (work->state_70.byte != 0) {
        hy0 = (hy0 + (ypack.w & -0x10000)) / 2;
    }

    code1 = Area_GetCellCode(x0, y0);
    code2 = Area_GetCellCode(x1, y1);
    key   = code1 & 0xF0;

    if (key == 0x70)
        goto case70;
    if (key < 0x71) {
        if (key == 0x30)
            goto shared52compute;
        if (key < 0x31) {
            if (key == 0x10)
                goto case10;
            if (key < 0x11) {
                if (key == 0x00)
                    goto block43;
                return code1 & BYTE_MASK;
            }
            if (key == 0x20)
                goto case20;
            return code1 & BYTE_MASK;
        }
        if (key == 0x50)
            goto shared52compute;
        if (key < 0x51) {
            if (key == 0x40)
                goto case40;
            return code1 & BYTE_MASK;
        }
        if (key == 0x60)
            goto block43;
        return code1 & BYTE_MASK;
    }
    if (key == 0xB0)
        goto block43;
    if (key < 0xB1) {
        if (key == 0x90)
            goto block43;
        if (key < 0x91) {
            if (key == 0x80)
                goto case80;
            return code1 & BYTE_MASK;
        }
        if (key == 0xA0)
            goto caseA0;
        return code1 & BYTE_MASK;
    }
    if (key == 0xD0)
        goto block43;
    if (key < 0xD1) {
        if (key == 0xC0)
            goto block43;
        return code1 & BYTE_MASK;
    }
    if (key == 0xE0)
        goto block43;
    if (key == 0xF0)
        return 0xFF;
    return code1 & BYTE_MASK;

case80:
    work = g_Task;
    if (work->unk_05 != 0)
        return 0xFF;
block43:
    if ((func_801BB6F0(code2 & BYTE_MASK) & BYTE_MASK) != 0)
        return 0xB0;
    if ((func_801BB760(hx0, hy0) & BYTE_MASK) == 0)
        return code1 & BYTE_MASK;
    return 0xFF;

case10:
    low = code1 & BYTE_MASK;
    if (low != 0x11)
        return 0xFF;
    work = g_Task;
    if (work == (Actor*)&D_8014626C)
        bit = D_80146277 & 1;
    else
        bit = g_Game.current->status.field.flags_12C.u8_value & 1;
    if (bit != 0)
        return 0;
    goto shared52compute;

case40:
    low = code1 & BYTE_MASK;
    goto shared52use;

shared52compute:
    low = code1 & BYTE_MASK;
shared52use:
    if (low != 0x52)
        return 0xFF;
    if ((func_801BB760(hx0, hy0) & BYTE_MASK) == 0)
        return 0;
    return 0xFF;

case70:
    if ((code2 & BYTE_MASK) != key)
        goto tail76;
    if ((func_801BB760(hx0, hy0) & BYTE_MASK) == 0)
        goto tail76;
    return 0x70;

case20:
    if ((func_801BB760(hx0, hy0) & BYTE_MASK) != 0)
        return 0xFF;
    low = code1 & 0xF1;
    if ((code2 & 0xF0) != key)
        return code1 & 0xF1;
    if (low != (code2 & 0xF1))
        goto retFF;
    return low;

retFF:
    return 0xFF;

caseA0:
    if ((code2 & BYTE_MASK) == 0xC0) {
        low = code1 & BYTE_MASK;
        if ((g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) != 0) {
            if (low == key)
                return 0;
            low = code1 & BYTE_MASK;
            if (low == 0xAE)
                return 0;
        } else {
            low = code1 & BYTE_MASK;
        }
        if (low == 0xAF)
            return 0xA1;
        work = g_Task;
        if (work->unk_05 != 0)
            return 0xFF;
        return low;
    }
    low = code1 & BYTE_MASK;
    if (low == 0xA2)
        goto retFF;
    if (low == 0xA3)
        goto retFF;
tail76:
    return -((func_801BB760(hx0, hy0) & BYTE_MASK) != 0) & BYTE_MASK;
}
#else
INCLUDE_ASM(func_801BB2B8);
#endif

#include "game_00.h"

MATCH s32 func_801C6658(s32 table_index, s32 table_slot, s32 entry_index, s32 selection) {
    u8* entry;
    s32 arg2b;
    s32 idx;
    /* FAKE: retail keeps cur_a in s7 while s6 carries sel. */
    MATCH_FAKE_PIN(s32, cur_a, "s7");
    s32 cur_b;
    s32 step_a;
    s32 step_b;
    s32 sel;
    s32 flip;
    s32 sub;
    s32 off;
    s32 count;
    s32 new_var;
    s32 tmp;
    s32 neg_a;
    s32 mask_a;
    s32 neg_b;

    arg2b = entry_index & BYTE_MASK;
    idx   = SQ(arg2b) + (table_index & BYTE_MASK);
    entry = ((table_slot & BYTE_MASK) * 8) + ((u8*)D_80181CA8 + (idx * 0x18));
    cur_a = *(s32*)entry;
    neg_a = -cur_a;
    cur_b = *(s32*)(entry + 4);
    if (neg_a <= 0) {
        s32 shifted = neg_a >> 0x1F;

        mask_a = -0x8000;
        step_a = shifted & mask_a;
    } else {
        step_a = 0x8000;
    }
    neg_b = -(*(s32*)(entry + 4));
    if (neg_b <= 0) {
        step_b = (neg_b >> 0x1F) & ~0x7FFF;
    } else {
        step_b = 0x8000;
    }
    sel = selection;
    if ((sel & BYTE_MASK) != 2) {
        s32 two = 2;
        tmp     = cur_a;
        do {
            cur_a  = cur_b;
            cur_b  = -tmp;
            tmp    = step_a;
            step_a = step_b;
            step_b = -tmp;
            sel    = (sel + 1) & 3;
            tmp    = cur_a;
        } while (sel != two);
    }
    flip = RANDOM_MASK(1);
    sel  = 0;
    sub  = table_slot & BYTE_MASK;
    off  = sub * 8;
    do {
        new_var                   = D_80143F28;
        count                     = 0;
        *(s32*)(D_80143F2C + off) = D_80143F24 + cur_a;
        *(s32*)(D_80143F30 + off) = new_var + cur_b;
        do {
            if (((func_801C6888(sub) & BYTE_MASK) != 0) && ((func_801C69C8(sub) & BYTE_MASK) != 0)) {
                D_801CD944[sub].active = 1;
                return 1;
            }
            if ((sel & BYTE_MASK) != flip) {
                *(s32*)(D_80143F2C + off) = *(s32*)(D_80143F2C + off) + step_a;
            } else {
                *(s32*)(D_80143F30 + off) = *(s32*)(D_80143F30 + off) + step_b;
            }
            count += 1;
        } while ((u32)(count & BYTE_MASK) < 8U);
        sel += 1;
    } while ((u32)(sel & BYTE_MASK) < 2U);
    return 0;
}

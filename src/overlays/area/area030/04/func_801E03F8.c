#include "area030_04.h"

/* Reflects the work velocity off the play-field bounds. */
/* nonmatching unmeasured: best 56.79%; row_delta and face_delta scored 47.53% (first mismatch +0x009C branch); next,
 * preserve the retail row-pointer, 0x19FFFF, and cue-table load order. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E03F8(void) {
    s32 upper_limit;
    s32 lower_limit;
    s32 value;
    s32 index;
    s32 vx;
    s32 vy;
    s32 pos_x;
    s32 pos_y;
    u8  direction;
    u8  entry_face;
    u8  row_facing;

    FISHING_STATE->pos_x_0C  = g_FacingOffsets[FISHING_STATE->counter_08].pos.x.raw;
    FISHING_STATE->cursor_10 = g_FacingOffsets[FISHING_STATE->counter_08].pos.y.raw;
    direction                = FISHING_STATE->counter_08;
    if (direction == 2 || direction == 6) {
        FISHING_STATE->pos_x_0C  = FISHING_STATE->pos_x_0C * 2;
        FISHING_STATE->cursor_10 = FISHING_STATE->cursor_10 * 2;
    }
    pos_x = FISHING_STATE->motion_34.pos.pos.x.raw;
    if (pos_x <= 0x80000) {
        FISHING_STATE->pos_x_0C = ABS(FISHING_STATE->pos_x_0C);
    } else if (pos_x > 0x13FFFF) {
        if (FISHING_STATE->pos_x_0C > 0) {
            FISHING_STATE->pos_x_0C = -FISHING_STATE->pos_x_0C;
        }
    }
    row_facing  = FISHING_ROW->facing_92;
    entry_face  = D_801E2AD3[FISHING_STATE->cue_index_06 * 0x24];
    upper_limit = (0x3E0000 - row_facing * 0xC0000) + entry_face * 0xF0000;
    lower_limit = (0x320000 - row_facing * 0xC0000) - entry_face * 0xF0000;
    if (upper_limit > 0x19FFFF) {
        value = 0x3E0000;
        if (upper_limit <= 0x3E0000) {
            value = upper_limit;
        }
    } else {
        value = 0x1A0000;
    }
    upper_limit = value;
    if (lower_limit > 0x10FFFF) {
        value = 0x320000;
        if (lower_limit <= 0x320000) {
            value = lower_limit;
        }
    } else {
        value = 0x110000;
    }
    lower_limit = value;
    pos_y       = FISHING_STATE->y_38.pos_y;
    if (pos_y < upper_limit) {
        if (pos_y <= lower_limit) {
            FISHING_STATE->cursor_10 = ABS(FISHING_STATE->cursor_10);
        }
    } else {
        if (FISHING_STATE->cursor_10 > 0) {
            FISHING_STATE->cursor_10 = -FISHING_STATE->cursor_10;
        }
    }
    for (index = 0; index < 8; index++) {
        vx    = g_FacingOffsets[index].pos.x.raw;
        value = vx;
        value = ABS(value);
        if (value < 0x401) {
            vx = vx * 2;
        }
        vy    = g_FacingOffsets[index].pos.y.raw;
        value = vy;
        value = ABS(value);
        if (value < 0x401) {
            vy = vy * 2;
        }
        if (FISHING_STATE->pos_x_0C != vx || FISHING_STATE->cursor_10 != vy) {
            continue;
        }
        break;
    }
    FISHING_STATE->counter_08 = index;
}
#else
INCLUDE_ASM(func_801E03F8);
#endif

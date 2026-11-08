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

    FISHING_STATE->pos_x_0C  = g_FacingOffsets[FISHING_STATE->counter_08].x;
    FISHING_STATE->cursor_10 = g_FacingOffsets[FISHING_STATE->counter_08].y;
    direction                = FISHING_STATE->counter_08;
    if (direction == 2 || direction == 6) {
        FISHING_STATE->pos_x_0C  = FISHING_STATE->pos_x_0C * 2;
        FISHING_STATE->cursor_10 = FISHING_STATE->cursor_10 * 2;
    }
    pos_x = FISHING_STATE->motion_34.unk_34;
    if (pos_x <= TO_COORD(8)) {
        FISHING_STATE->pos_x_0C = ABS(FISHING_STATE->pos_x_0C);
    } else if (pos_x > 0x13FFFF) {
        if (FISHING_STATE->pos_x_0C > 0) {
            FISHING_STATE->pos_x_0C = -FISHING_STATE->pos_x_0C;
        }
    }
    row_facing  = FISHING_ROW->facing_92;
    entry_face  = D_801E2AD3[FISHING_STATE->cue_index_06 * 0x24];
    upper_limit = (TO_COORD(62) - row_facing * TO_COORD(12)) + entry_face * TO_COORD(15);
    lower_limit = (TO_COORD(50) - row_facing * TO_COORD(12)) - entry_face * TO_COORD(15);
    if (upper_limit > 0x19FFFF) {
        value = TO_COORD(62);
        if (upper_limit <= TO_COORD(62)) {
            value = upper_limit;
        }
    } else {
        value = TO_COORD(26);
    }
    upper_limit = value;
    if (lower_limit > 0x10FFFF) {
        value = TO_COORD(50);
        if (lower_limit <= TO_COORD(50)) {
            value = lower_limit;
        }
    } else {
        value = TO_COORD(17);
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
        vx    = g_FacingOffsets[index].x;
        value = vx;
        value = ABS(value);
        if (value < 0x401) {
            vx = vx * 2;
        }
        vy    = g_FacingOffsets[index].y;
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

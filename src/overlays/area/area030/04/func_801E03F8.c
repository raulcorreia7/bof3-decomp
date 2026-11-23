#include "area030_04.h"

/* Reflects the work velocity off the play-field bounds. */
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

    TASK(FishingState)->pos_x     = g_FacingOffsets[TASK(FishingState)->counter_08].x;
    TASK(FishingState)->cursor_10 = g_FacingOffsets[TASK(FishingState)->counter_08].y;
    direction                     = TASK(FishingState)->counter_08;
    if (direction == 2 || direction == 6) {
        TASK(FishingState)->pos_x     = TASK(FishingState)->pos_x * 2;
        TASK(FishingState)->cursor_10 = TASK(FishingState)->cursor_10 * 2;
    }
    pos_x = TASK(FishingState)->motion.unk_34;
    if (pos_x <= TO_COORD(8)) {
        if (TASK(FishingState)->pos_x < 0) {
            TASK(FishingState)->pos_x = -TASK(FishingState)->pos_x;
        }
    } else if (pos_x > 0x13FFFF && TASK(FishingState)->pos_x > 0) {
        TASK(FishingState)->pos_x = -TASK(FishingState)->pos_x;
    }
    row_facing  = FISHING_ROW->fish_row;
    upper_limit = TO_COORD(62) - row_facing * TO_COORD(12);
    entry_face  = D_801E2AD3[TASK(FishingState)->cue_index * sizeof(FishingSceneCue)];
    upper_limit += entry_face * TO_COORD(15);
    lower_limit = TO_COORD(50) - row_facing * TO_COORD(12) - entry_face * TO_COORD(15);
    /* Clamp the two bounds to 26..62 and 17..50 cells; the tests are > floor - 1. */
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
    pos_y       = TASK(FishingState)->y_38.pos_y;
    if (pos_y < upper_limit) {
        if (pos_y <= lower_limit) {
            if (TASK(FishingState)->cursor_10 < 0) {
                TASK(FishingState)->cursor_10 = -TASK(FishingState)->cursor_10;
            }
        }
    } else {
        if (TASK(FishingState)->cursor_10 > 0) {
            TASK(FishingState)->cursor_10 = -TASK(FishingState)->cursor_10;
        }
    }
    for (index = 0; index < 8; index++) {
        vx    = g_FacingOffsets[index].x;
        value = vx;
        if (value < 0) {
            value = -value;
        }
        if (value < 0x401) {
            vx = vx * 2;
        }
        vy    = g_FacingOffsets[index].y;
        value = vy;
        if (value < 0) {
            value = -value;
        }
        if (value < 0x401) {
            vy = vy * 2;
        }
        if (TASK(FishingState)->pos_x != vx || TASK(FishingState)->cursor_10 != vy) {
            continue;
        }
        break;
    }
    TASK(FishingState)->counter_08 = index;
}
#else
INCLUDE_ASM(func_801E03F8);
#endif

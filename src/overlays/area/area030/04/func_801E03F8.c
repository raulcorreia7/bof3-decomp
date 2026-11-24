#include "area030_04.h"

/* Reflects the work velocity off the play-field bounds. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E03F8(void) {
    /* FAKE: Keep the 62-cell ceiling in a3 for the matching bounds. */
    FAKE_REG(s32, max_y, "a3");
    /* FAKE: Keep the 26-cell floor in a2 before the row loads. */
    FAKE_REG(s32, upper_floor, "a2");
    /* FAKE: Keep the 17-cell floor in v0 for the lower-bound test. */
    FAKE_REG(s32, lower_floor, "v0");
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
    /* FAKE: Keep the row offset in a0 for both bound calculations. */
    FAKE_REG(s32, row_offset, "a0");
    s32 lower_base;

    TASK(FishingState)->pos_x     = g_FacingOffsets[TASK(FishingState)->counter_08].x;
    TASK(FishingState)->cursor_10 = g_FacingOffsets[TASK(FishingState)->counter_08].y;
    direction                     = TASK(FishingState)->counter_08;
    if (direction == 2 || direction == 6) {
        TASK(FishingState)->pos_x     = TASK(FishingState)->pos_x * 2;
        TASK(FishingState)->cursor_10 = TASK(FishingState)->cursor_10 * 2;
    }
    pos_x = TASK(FishingState)->motion.unk_34;
    /* FAKE: Keep the x clamp before the y-bound constants like retail. */
    FAKE_ORDER_LOCK(
        if (pos_x <= TO_COORD(8)) {
            if (TASK(FishingState)->pos_x < 0) {
                TASK(FishingState)->pos_x = -TASK(FishingState)->pos_x;
            }
        } else if (pos_x > 0x13FFFF && TASK(FishingState)->pos_x > 0) { TASK(FishingState)->pos_x = -TASK(FishingState)->pos_x; });
    upper_floor = 0x19FFFF;
    row_facing  = FISHING_ROW->fish_row;
    row_offset  = row_facing * TO_COORD(12);
    max_y       = TO_COORD(62);
    upper_limit = max_y - row_offset;
    entry_face  = D_801E2AD3[TASK(FishingState)->cue_index * sizeof(FishingSceneCue)];
    upper_limit += entry_face * TO_COORD(15);
    lower_base  = TO_COORD(50) - row_offset;
    lower_limit = lower_base - entry_face * TO_COORD(15);
    /* FAKE: Keep the y-bound threshold setup after the x clamp like retail. */
    FAKE_ORDER_LOCK(
        if (upper_limit > upper_floor) {
            value = max_y;
            if (upper_limit <= max_y) {
                value = upper_limit;
            }
        } else { value = TO_COORD(26); });
    upper_limit = value;
    /* FAKE: Keep the ceiling in a3 through the bound comparison. */
    FAKE_USE(max_y);
    lower_floor = 0x10FFFF;
    if (lower_limit > lower_floor) {
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

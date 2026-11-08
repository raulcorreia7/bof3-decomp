#include "game_00.h"

MATCH bool func_801C7498(s32 from_x, s32 from_y, s32 to_x, s32 to_y, u8 reach, u8 other_reach) {
    s32 combined_limit;
    s32 extent;
    s32 delta_x;
    s32 other_extent;
    s32 combined_limit_y;
    s32 delta_y;

    extent         = (reach + 1) << 0xF;
    other_extent   = (other_reach + 1) << 0xF;
    delta_x        = from_x - to_x;
    combined_limit = extent + other_extent;
    if (delta_x > 0) {
        if (delta_x < combined_limit) {
            goto check_y; /* x axis within reach, test y next */
        }
        goto outside_reach; /* the x axis is out of reach */
    }
    if ((to_x - from_x) < combined_limit) {
        goto check_y; /* the x axis is within reach, test y next */
    }
    goto outside_reach; /* the x axis is out of reach */
check_y:
    delta_y          = from_y - to_y;
    combined_limit_y = extent + other_extent;
    if (delta_y > 0) {
        if (delta_y < combined_limit_y) {
            goto within_reach; /* both axes within reach */
        }
        goto outside_reach; /* the y axis is out of reach */
    }
    if ((to_y - from_y) < combined_limit_y) {
        goto within_reach; /* both axes are within reach */
    }
    goto outside_reach; /* the y axis is out of reach */
within_reach:
    return 0;
outside_reach:
    return 1;
}

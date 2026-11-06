#include "battle_03.h"

MATCH u8 func_801DE92C(void) {
    s16 target_offset;
    s16 index_offset;
    u8  index;
    u8  target;

    target_offset = 0xC328u;
    index_offset  = 0xBF04u;
    target        = D_801F0000[target_offset];
    index         = D_801F0000[index_offset];
    return index != target;
}

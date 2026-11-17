#include "battle_03.h"

/* func_801EAB38 */
MATCH u8 Battle_AdvanceMessage(void) {
    u8* const base = ((u8*)&D_801F0000);
    s16       target_offset;
    s16       index_offset;
    u8        index;
    u8        target;

    target_offset      = 0xC328u;
    index_offset       = 0xBF04u;
    index              = base[index_offset];
    target             = base[target_offset];
    index              = (index + 1u) & 0xFu;
    base[index_offset] = index;
    return (target ^ index) == 0u;
}

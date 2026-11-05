#include "area030_04.h"

/* Picks a randomised reaction tier from the distance between the
 * scratch byte at 0x0A and current_byte, scaled by the per-state threshold, and returns
 * whether the drawn nibble falls below it. */
MATCH s32 func_801E02D4(u8 current_byte, u8 target_byte) {
    u32 raw;
    u32 threshold;
    s32 diff;
    s32 distance;
    s32 masked_flag;
    s32 flag;

    raw = (D_801E320C->unk_03 * 8 + 0x18) * target_byte;
    /* FAKE: retail evaluates the threshold before the scratch read. */
    MATCH_BARRIER();
    /* FAKE: retail reads the byte at +0x0A signed (lb). */
    distance = *(s8*)&((u8*)g_SpadWork)[0x0A] - current_byte;
    if (distance < 0) {
        distance = -distance;
    }

    /* FAKE: holds the masked remainder out of the abs branch delay slot. */
    MATCH_BARRIER();
    diff      = distance & BYTE_MASK;
    threshold = raw & BYTE_MASK;
    if (diff < (threshold >> 2)) {
        flag = 1;
    } else if (diff < (threshold >> 1)) {
        flag = 2;
    } else if (diff < threshold) {
        flag = 4;
    } else if (diff < (s32)(threshold << 2)) {
        flag = 8;
    } else {
        flag = 0xE;
    }

    masked_flag = flag & BYTE_MASK;
    return (RANDOM_MASK(0xF)) < masked_flag;
}

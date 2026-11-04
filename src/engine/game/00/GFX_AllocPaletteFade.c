#include "game_00.h"

MATCH s32 GFX_AllocPaletteFade(u8* color_data, s32 palette_base, s32 palette_count, s32 palette_index, s32 flag_value) {
    s32 slot;   /* entry index 0-31 */
    s32 offset; /* byte offset into entry table, slot * 12 */
    s32 result; /* narrowed slot for the step call and return */
    s32 value;  /* flag value derived from flag_value, stored as a byte */
    s32 flagged;
    u8  tmp_a;
    u8  tmp_b;

    slot    = 0;
    offset  = 0;
    value   = flag_value * 2 + 0x41;
    flagged = value | 0x80;
loop_1:
    if ((((u8*)D_80145BD4)[offset] & 1) == 0) {
        ((u8*)D_80145BD4)[offset] = (u8)value;
        if ((color_data[0x28] == 0) && ((color_data[0x24] & 4) == 0)) {
            ((u8*)D_80145BD4)[offset] = (u8)flagged;
        }
        result                                             = slot & BYTE_MASK;
        ((u8*)D_80145BD4)[offset + 6]                      = GFX_MarkPaletteCells(color_data[0x28], (u8)result, 1);
        tmp_a                                              = color_data[0x27];
        ((u8*)D_80145BD4)[offset + 1]                      = tmp_a;
        tmp_b                                              = color_data[0x28];
        ((PaletteFade*)((u8*)D_80145BD4 + offset))->target = color_data;
        ((u8*)D_80145BD4)[offset + 2]                      = palette_base;
        ((u8*)D_80145BD4)[offset + 3]                      = palette_count;
        ((u8*)D_80145BD4)[offset + 4]                      = palette_index;
        ((u8*)D_80145BD4)[offset + 5]                      = tmp_b;
        return result;
    }
    slot += 1;
    offset += 0xC;
    if (slot >= 32) {
        return 0xFF;
    }
    goto loop_1; /* try the next slot */
}

#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_8019625C(void) {
    /* FAKE: pin carries entry pointer in t1. */
    MATCH_REG(PaletteFade*, entry, "$9");
    s32 entry_index;
    /* FAKE: pin holds loop counter in t2. */
    MATCH_REG(s32, color_index, "$10");
    s32 count;
    u32 value;
    u32 table_index;
    u32 divisor;
    u32 quotient;
    u32 remainder;
    u32 source_index;
    u32 destination_index;
    /* FAKE: pin loads palette scale into a3. */
    MATCH_REG(u32, scale, "$7");
    volatile u16* source;
    u16*          destination;
    u16           color;
    s8            red;
    s8            green;
    /* FAKE: pin accumulates blue channel in t0. */
    MATCH_REG(s8, blue, "$8");
    u8 high_bit;

    for (entry_index = 0; entry_index < 32; entry_index++) {
        entry = &D_80145BD4[entry_index];
        if ((entry->flags & 1u) != 0u) {
            value             = entry->saved_byte;
            table_index       = entry->table_index;
            divisor           = s_PaletteFadeDivisors[table_index];
            quotient          = value / divisor;
            source_index      = value % divisor;
            remainder         = entry->step / divisor;
            destination_index = entry->step % divisor;
            scale             = s_PaletteFadeScales[table_index];
            count             = s_PaletteFadeCounts[table_index] << 4;
            source_index      = (u8)(scale * source_index);
            destination_index = (u8)(scale * destination_index);
            source            = g_GraphicsPaletteDst + quotient * 256u;
            destination       = MEM_PTR(u16, AREA_PALETTE_WORK) + remainder * 256u;

            for (color_index = 0; color_index < count; color_index++) {
                high_bit = 1u;
                if ((entry->flags & 2u) == 0u) {
                    high_bit = (u8)(source[source_index] >> 15);
                    color    = source[source_index];
                }

                red   = (s8)(color & 0x1Fu);
                green = (s8)((color >> 5) & 0x1Fu);
                blue  = (s8)((color >> 10) & 0x1Fu);

                red   = (s8)(red + entry->red_offset);
                value = red < 0;
                if (value) {
                    red = 0;
                } else if (red >= 0x20) {
                    red = 0x1F;
                }

                green = (s8)(green + entry->green_offset);
                if (green < 0) {
                    green = 0;
                } else if (green >= 0x20) {
                    green = 0x1F;
                }

                blue = (s8)(blue + entry->blue_offset);
                if (blue < 0) {
                    blue = 0;
                } else if (blue >= 0x20) {
                    blue = 0x1F;
                }

                if (color_index == 0u) {
                    destination[destination_index] = 0u;
                } else {
                    destination[destination_index + color_index] =
                        (u16)((red << 10) | (((high_bit << 15) | (blue << 10)) | (green << 5)));
                }
                source_index++;
            }

            g_GfxPalettePending = 1u;
            if ((entry->flags & 0x40u) != 0u) {
                entry->flags &= 0xBFu;
                entry->target[0x27] = entry->step;
                if ((entry->flags & 0x80u) != 0u) {
                    entry->target[0x24] |= 4u;
                }
            }
        }
    }
}
#else
INCLUDE_ASM(func_8019625C);
#endif

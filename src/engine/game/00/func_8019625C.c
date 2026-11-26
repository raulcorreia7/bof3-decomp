#include "game_00.h"

/* Steps each active palette fade: copies its cells into the work palette with the fade offset, each channel clamped. */
MATCH void func_8019625C(void) {
    PaletteFade* fade;
    s32          i;
    s32          j;
    u16          count;
    u8           divisor;
    u8           scale;
    u8           src_bank;
    u8           src_cell;
    u8           dst_bank;
    u8           dst_cell;
    u16*         src;
    u16*         dst;
    u16          color;
    u8           high;
    s8           r;
    s8           g;
    s8           b;

    for (i = 0; i < PALETTE_FADE_COUNT; i++) {
        fade = &g_PaletteFades[i];
        if (fade->flags & PALETTE_FADE_ACTIVE) {
            divisor  = s_PaletteFadeDivisors[fade->table_index];
            src_bank = fade->saved_byte / divisor;
            src_cell = fade->saved_byte % divisor;
            dst_bank = fade->cell_index / divisor;
            dst_cell = fade->cell_index % divisor;
            scale    = s_PaletteFadeScales[fade->table_index];
            src_cell = scale * src_cell;
            dst_cell = scale * dst_cell;
            count    = s_PaletteFadeCounts[fade->table_index] << 4;
            for (j = 0; j < count; j++) {
                src  = g_GraphicsPaletteDst + src_bank * 256;
                dst  = MEM_PTR(u16, AREA_PALETTE_WORK) + dst_bank * 256;
                high = 1;
                if (!(fade->flags & 2)) {
                    high = src[src_cell + j] >> 15;
                }
                color = src[src_cell + j];
                b     = (color >> 10) & 0x1F;
                g     = (color >> 5) & 0x1F;
                r     = color & 0x1F;
                r += fade->offset.r;
                r = (r >= 0) ? ((r < 0x20) ? r : 0x1F) : 0;
                g += fade->offset.g;
                g = (g >= 0) ? ((g < 0x20) ? g : 0x1F) : 0;
                b += fade->offset.b;
                b = (b >= 0) ? ((b < 0x20) ? b : 0x1F) : 0;
                if (j == 0) {
                    dst[dst_cell + j] = 0;
                } else {
                    dst[dst_cell + j] = r | ((high << 15) | (b << 10) | (g << 5));
                }
            }
            g_GfxPalettePending = 1;
            if (fade->flags & 0x40) {
                fade->flags &= ~0x40;
                fade->target->saved_byte = fade->cell_index;
                if (fade->flags & 0x80) {
                    fade->target->flags |= 4;
                }
            }
        }
    }
}

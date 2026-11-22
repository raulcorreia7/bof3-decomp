#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FCA3C(u32 mode) {
    u8  row;
    u16 col;
    u32 row_base;
    u32 palette;
    u16 color;
    u16 red;
    u16 green;
    u16 blue;
    u16 average;
    u16 flag;

    row     = 0;
    palette = AREA_PALETTE_WORK;
    do {
        if (row != 11) {
            col      = 0;
            row_base = row * AREA_PALETTE_ROW + palette;
            do {
                color   = *MEM_PTR(u16, col * 2 + row_base);
                red     = color & 0x1F;
                green   = (color >> 5) & 0x1F;
                blue    = (color >> 10) & 0x1F;
                flag    = color & 0x8000;
                average = (red + green + blue) / 3;
                if ((u8)mode != 0) {
                    *MEM_PTR(u16, col * 2 + row_base) = flag | (average << 10) | (average << 5) | average;
                } else {
                    if (red != average) {
                        red += (average - red >= 0) ? 1 : -1;
                    }
                    if (green != average) {
                        green += (average - green >= 0) ? 1 : -1;
                    }
                    if (blue != average) {
                        blue += (average - blue >= 0) ? 1 : -1;
                    }
                    *MEM_PTR(u16, col * 2 + row_base) = flag | (blue << 10) | (green << 5) | red;
                }
                col++;
            } while (col < AREA_PALETTE_COLORS);
        }
        row++;
    } while (row < AREA_PALETTE_ROWS);
    g_GfxPalettePending = 1;
}

#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FCA3C(u32 mode) {
    u16* cell;
    u32  row;
    u32  col;
    u32  row_base;
    u16  color;
    u16  red;
    u16  green;
    u32  blue;
    u16  average;
    u16  flag;

    row = 0;
    do {
        if ((row & 0xFF) != 11) {
            col      = 0;
            row_base = AREA_PALETTE_WORK + (row & 0xFF) * AREA_PALETTE_ROW;
            do {
                cell    = MEM_PTR(u16, (col & 0xFFFF) * 2 + row_base);
                color   = *cell;
                red     = color & 0x1F;
                green   = (color >> 5) & 0x1F;
                blue    = (color >> 10) & 0x1F;
                average = (red + green + blue) / 3;
                flag    = color & 0x8000;
                if ((u8)mode != 0) {
                    *cell = average | flag | (average << 10) | (average << 5);
                } else {
                    if (red != average) {
                        if (average - red >= 0) {
                            red = red + 1;
                        } else {
                            red = red - 1;
                        }
                    }
                    if (green != average) {
                        if (average - green >= 0) {
                            green = green + 1;
                        } else {
                            green = green - 1;
                        }
                    }
                    if (blue != average) {
                        if (average - blue >= 0) {
                            blue = blue + 1;
                        } else {
                            blue = blue - 1;
                        }
                    }
                    *cell = red | flag | (blue << 10) | (green << 5);
                }
                col++;
            } while ((col & 0xFFFF) < AREA_PALETTE_COLORS);
        }
        row++;
    } while ((row & 0xFF) < AREA_PALETTE_ROWS);
    g_GfxPalettePending = 1;
}
#else
INCLUDE_ASM(func_801FCA3C);
#endif

#include "area091_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3318(void) {
    u16* src;
    u16* dst;
    u16  color_a;
    u16  color_b;
    u32  row;
    u32  col;
    u8   cell;
    u8   index;

    g_Task->unk_0A--;
    if (g_Task->unk_0A != 0) {
        cell    = g_Task->unk_27;
        index   = g_Task->param.unk_0B;
        row     = (cell >> 3) * AREA_PALETTE_ROW;
        col     = (cell & 7) * AREA_PALETTE_UNIT;
        src     = MEM_PTR(u16, AREA_PALETTE_ARENA + row + col);
        color_a = (src[index] & 0x7BDE) >> 1;
        color_b = (src[31 - index] & 0x7BDE) >> 1;
    } else {
        cell    = g_Task->unk_27;
        index   = g_Task->param.unk_0B;
        row     = (cell >> 3) * AREA_PALETTE_ROW;
        col     = (cell & 7) * AREA_PALETTE_UNIT;
        src     = MEM_PTR(u16, AREA_PALETTE_ARENA + row + col);
        color_a = src[index];
        color_b = src[31 - index];
    }
    dst             = MEM_PTR(u16, AREA_PALETTE_WORK + row + col);
    dst[index]      = color_a;
    dst[31 - index] = color_b;
    if (g_Task->unk_0A == 0) {
        g_Task->unk_0A = 2;
        if (++g_Task->param.unk_0B == 0x10) {
            g_Task->unk_0A = 0x1E;
            g_Task->unk_04++;
        }
    }
    g_GfxPalettePending++;
    func_801F2ED4(300, 0xFF);
}
#else
INCLUDE_ASM(func_801F3318);
#endif

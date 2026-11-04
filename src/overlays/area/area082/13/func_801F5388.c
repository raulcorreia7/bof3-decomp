#include "area082_13.h"

/* Body: scale each 5-bit channel of 256 u16 colors at 0x80034000 by the argument >> 7, keep bit 15, write them to 0x80038000, set g_GfxPalettePending. First differing instruction: andi v1,a0,0xFFFF (candidate) where retail multiplies the red channel first; the red-first order did not survive loop, local and single-expression forms. */
INCLUDE_ASM(func_801F5388);

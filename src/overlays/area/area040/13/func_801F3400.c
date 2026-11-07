#include "area040_13.h"

/* hint: control flow and the 4x4 palette-clear loop match; the cell coordinates (arg >> 16) are computed into a0/a1 after the func_801F369C call and copied to s0/s1, where every C form hoists them into s0/s1 first. First differing instruction: sra a0,s2,0x10 at +0x80. */
INCLUDE_ASM(func_801F3400);

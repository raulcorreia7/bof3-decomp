#include "area168_13.h"

/* tried: none (skipped for tractable functions first pass); needs D_801F4B30
 * (u8[6] table) declaration and scratchpad 0x1F800044 pointer write
 * (*(u8*)((*(u32*)0x1F800044)+1)=1); loop calls func_801A4BC0(0x10, table[i], 0x89) */
INCLUDE_ASM(func_801F2C7C);

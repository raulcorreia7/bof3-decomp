#include "magic080_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EECE4};

    table[SP_REF(u8*, 0x44)[1]]();
}

/* Scheduling and regalloc residual: the target-Y load stays above the coord_x store while retail
 * pins it below, and the spad pointer and target-X swap v0/v1 (first difference lui v1,0x1f80 at
 * 0x801EEC5C); plain, saved-target and hybrid target forms all give the same schedule. */
INCLUDE_ASM(func_801EEC5C);

/* Regalloc: the m2c draft with the arg-less else call matches except that the spad pointer and
 * the halfword value swap v0/v1; first difference lui v0 at 0x801EECF4. */
INCLUDE_ASM(func_801EECE4);

INCLUDE_ASM(func_801EED94);

INCLUDE_ASM(func_801EEF5C);

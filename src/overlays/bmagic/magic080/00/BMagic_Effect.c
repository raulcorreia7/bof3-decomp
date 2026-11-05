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

/* Regalloc: the no-local form (inline cell reads, arg-less else call) differs only in the tie
 * where the spad pointer takes v1 and the half value v0 (first difference lui v1, 0x801EECF4); a
 * u8 local reproduces retail's v0/v1 roles but materializes andi a0,a0,0xff for the promoted call
 * argument (0x801EED0C), and an s32 or register local loses both. */
INCLUDE_ASM(func_801EECE4);

INCLUDE_ASM(func_801EED94);

INCLUDE_ASM(func_801EEF5C);

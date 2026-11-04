#include "area189_13.h"

/* u8*+FIELD with one s32 temp gives the right order but puts the axis sum in
 * v1 (retail v0) and adds one instruction; first difference 0x801F55A8 lw
 * v1,52(a0) vs lw v0,52(a0). */
INCLUDE_ASM(func_801F559C);

#include "area082_13.h"

/* Slide step: unk_30 += 0x80, unk_32 counts down, at zero Area_ClearWorkColumn then unk_32 = 0x12C, step++ and cue 0x209. Control flow matches in three forms; first difference is the work register (retail v0, candidate a0) at the first lui 0x1f80. */
INCLUDE_ASM(func_801F3398);

#include "area052_13.h"

/* resume: best 2 differing (STACK_PADS(u8, 16) fixes the frame rows; the residual is the sample shift: retail shifts the ABI-extended s16 return raw (sll v0,v0,8), our build materializes the s16 view first (sll16/sra8 combined with the shift) - the same s16 prototype serves func_801F57FC where the s32 local absorbs the call for free, but the <<8 use re-materializes the view); first `!` +0x70 (sll v0,v0,0x10 pair vs sll 0x8); next lever: a spelling whose shift input hides the s16 range from the compiler, else the known-compiler-residual route. */
INCLUDE_ASM(func_801F431C);

#include "area135_14.h"

/* Index-local draft ((u8)(g_ScriptState->pad_03 - 6) * 2 per branch, u8* flags = &D_80143FBC tail) matches
 * frame, pair loads and tail; the residual is one register/schedule permutation (retail keeps step in a1 and y
 * in a2, duplicates the index andi per branch and holds li a0 in the bne delay; candidate mirrors them, 0xA4
 * against 0xA8). The shared-index form of the pair loads costs 8 bytes of frame per branch: use the idx local.
 * First differing instruction: addiu a1,v0,-6 (retail) against addiu a0 (candidate) at 0x801F41E4. Permuter tried
 * (70k iterations, score plateaued at 485). */
INCLUDE_ASM(func_801F41C8);

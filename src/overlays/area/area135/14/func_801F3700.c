#include "area135_14.h"

/* Body: the opening-frame box (step * 25 wide, step * 6 high, centered on the (0xC8, 0x30) panel at D_801F6210/D_801F6212) drawn by func_80159FA0 with s16 x and y, plus the unk_09 step counter. First differing instruction: sll a3,a3,1 (retail) against sll a0,a0,16 (candidate) after the frame is 0x20 bytes with STACK_PADS(u8, 8); the in-body, inline-helper and local-variable forms all schedule the s16 casts earlier. */
INCLUDE_ASM(func_801F3700);

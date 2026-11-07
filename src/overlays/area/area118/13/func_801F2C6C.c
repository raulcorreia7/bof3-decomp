#include "area118_13.h"

/* hint: the packed clock word (low byte count, bits 8-14 frames, bit 15 phase) loads once and the phase shifts out before the move to a0; every C form copies the word first. First differing instruction: srl a1,v0,0xf at +0x78. */
INCLUDE_ASM(func_801F2C6C);

#include "area140_13.h"

/* resume: best 5 differing (the kept selector andi shapes: `u8 flag; u16 word = flag;` with the sub on the raw register keeps `andi v1,v1,0xFF` but hoists it before the branch where retail keeps it in the bnez delay slot); first mismatch +0x14 (lui v1 vs v0, the load register); next lever: place `word = flag` in the second test's arm so dbr fills the delay slot, then the permuter. */
INCLUDE_ASM(func_801F3DAC);

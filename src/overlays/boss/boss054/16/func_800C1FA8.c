#include "boss054_16.h"

/* nonmatching: pure C is exact up to 0x800C1FF0; retail adds 0x180 to the Area_SampleHeight result in v0 without the sll/sra extension (retail addiu v0,v0,384, candidate sll v0,v0,16), so the call reads as returning s32. */
INCLUDE_ASM(func_800C1FA8);

#include "area052_13.h"

/* Best 9 differing (STACK_PADS(u8, 32), s32 height local). First ! row: the s16
 * guard pair sll v0,16 / sra v0,8 at 0x801F42F8: the shared s16
 * Area_SampleHeight prototype truncates the shifted return, retail shifts the
 * raw s32 (needs.tsv). Frame is 0x28 with only ra and s0 saved. */
INCLUDE_ASM(func_801F4290);

#include "boss028_16.h"

/* Fall step: span_3E += unk_14, unk_14 += unk_20; when span_3E is below Area_SampleHeight(x, y) + 0x200 it snaps to that height, stops (unk_14 0, unk_20 0x40), plays cue 0x600 and steps unk_02 by one, or two once unk_09 is spent. First differing
 * instruction lw t0,20(v0) retail against lw a3,20(v0); the candidate is 12 bytes longer because retail compares the call result without the halfword sign extension the s16 prototype adds. needs: type (Area_SampleHeight result read as a word here). */
INCLUDE_ASM(func_800C1D90);

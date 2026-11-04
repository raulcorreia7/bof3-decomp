#include "area135_14.h"

/* Body: delta = (s16)(arg - z.part.integer), unk_09 = abs(delta / 128) << 4, vz = delta / unk_09, unk_10 = 0, unk_0C = 0; the header prototype should be void with a 16-bit argument. First differing instruction: lui v1 (retail, the scratch pointer in v1 and delta kept in a0) against lui a1 (candidate, delta lands in v1 and the pointer in a1); the s32 and s16 parameter, local and in-place forms all allocate the same way. */
INCLUDE_ASM(func_801F5BCC);

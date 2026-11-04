#include "area120_13.h"

/* Body: step counter at +0x09 (u8, +1), triangle delta 8 - abs(8 - step), state_02 = 2 and step = 0 once step >= 0x10, then func_801F3F5C(0x80, 0x40, 1, -(8 - delta) << 4). First differing instruction: lui a1 (retail, second scratch pointer in a1 with the constant 8 in a0) against lui v1 (candidate, pointer CSE kept in v1); work/scratch locals and a height temp all schedule the reload in v-registers. */
INCLUDE_ASM(func_801F3DF0);

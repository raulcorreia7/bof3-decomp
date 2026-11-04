#include "area088_13.h"

/* Body: seed x, y, z of the work row, D_800E4B3E = 0x60, 32 calls to func_801F2F28(0x800E4800), then clear unk_09 and step unk_01. First differing instruction: lui v0,0x1 (retail) against li v0,0x60 (candidate); the compiler hoists the D_800E4B3E constant above the x store in plain, local-pointer and for-loop forms. */
INCLUDE_ASM(func_801F2C48);

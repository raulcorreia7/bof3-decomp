#include "area134_13.h"

/* Either D_80146865 is 0xFF or D_80146866 is 0x80: step 0x17, else clear D_80146865 and the step; then clear state_02. With u8 flag pointer to D_80146865 the flow matches; first difference is the work pointer register (retail v0, candidate v1) at the second lui 0x1f80. */
INCLUDE_ASM(func_801F33C0);

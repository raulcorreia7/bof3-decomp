#include "area108_14.h"

/* first differing instruction: beq v1,v0,0x801F42E8 (retail) against 0x801F42E4 (candidate); retail repeats lui+addiu a0 = &D_801448ED in each case and stores the state byte before a0 += 0x63B for SYS_SetFlag, 0x88 bytes against 0x80; switch, pointer local and a pointer bump tried. */
INCLUDE_ASM(func_801F4298);

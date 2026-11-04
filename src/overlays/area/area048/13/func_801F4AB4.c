#include "area048_13.h"

/* first differing instruction: beq v1,v0,0x801F4AFC (retail) against 0x801F4B04 (candidate); the body sets Actor.unk_77 to 7, 6, 8 or 9 by D_8014686B (6, 2, 8, other) and unk_7E to 0xFFFE, with a g_CurrentActor reload in each arm; switch, shared step local and an if chain tried (0x8C bytes retail, 0x94, 0x7C, 0x78). */
INCLUDE_ASM(func_801F4AB4);

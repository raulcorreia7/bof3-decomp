#include "area135_14.h"

/* Body: if D_80143F03 is 4, 6 or 7 and SYS_TestFlag(g_SceneEventFlags, 0xC) holds and (u8)func_801F603C(arg0, arg1) is nonzero, call func_801BE1B0(0) and return 1, else 0. First differing instruction: lui a0 (retail keeps the lbu mode in a0 with a separate andi v1,a0,0xFF) against lui v1 (candidate); the s32 and u8 mode local, the direct global and the masked forms all give the same 0x90-byte body against retail 0x94. */
INCLUDE_ASM(func_801F5208);

#include "area198_13.h"

/* resume: best 2 differing (the unk_0B byte load lands in v0 where retail keeps v1, the g_SpadWork pointer register; the retail frame carries 8 unused bytes - STACK_PADS(u8, 8) with a FAKE note fixes the frame rows); first `!` +0x44 (lbu v1 vs v0); next lever: the permuter on the load register tie, tried byte local and work local. */
INCLUDE_ASM(func_801F3600);

#include "area056_13.h"

/* first differing instruction: retail stores g_MessageRequest first (li v0,0xFFFF) and delays the stack frame, candidate opens with addiu sp; candidate is 4 bytes longer; plain, early-return and nested forms tried */
INCLUDE_ASM(func_801F3200);

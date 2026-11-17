#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801EFCE8(void) {
}
#else
INCLUDE_ASM(func_801EFCE8);
#endif

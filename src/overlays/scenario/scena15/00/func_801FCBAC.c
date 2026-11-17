#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FCBAC(void) {
}
#else
INCLUDE_ASM(func_801FCBAC);
#endif

#include "commu02_08.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801D0FE0(void) {
}
#else
INCLUDE_ASM(func_801D0FE0);
#endif

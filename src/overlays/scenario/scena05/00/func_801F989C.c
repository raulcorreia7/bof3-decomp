#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F989C(void) {
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F98A4(void) {
}
#else
INCLUDE_ASM(func_801F98A4);
#endif

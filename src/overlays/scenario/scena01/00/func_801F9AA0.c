#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801F9AA0(void) {
}
#else
INCLUDE_ASM(func_801F9AA0);
#endif

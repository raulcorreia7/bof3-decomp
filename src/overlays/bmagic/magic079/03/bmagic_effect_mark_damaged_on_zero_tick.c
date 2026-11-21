#include "magic079_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EED98 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEDDC(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F02B4, func_801EF458);
}

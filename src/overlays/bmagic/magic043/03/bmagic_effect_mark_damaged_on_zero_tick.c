#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF360 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF3A4(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(D_801EFC8C, func_801EF72C, func_801EF7F8);
}
